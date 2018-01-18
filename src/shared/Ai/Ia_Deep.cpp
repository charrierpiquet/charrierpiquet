#include "Ia_Deep.h"
#include "Engine/CommandDraw.h"
#include "Engine/CommandUntap.h"
#include "Engine/CommandPriority.h"
#include "Engine/CommandPhase.h"
#include "Engine/CommandClean.h"
#include "Engine/CommandDie.h"
#include "Engine/CommandResolveCapa.h"
#include "Engine/CommandDiscard.h"
#include "Engine/CommandPaye.h"
#include "Engine/CommandAttack.h"
#include "Engine/CommandBlock.h"
#include "Engine/CommandCast.h"
#include "Engine/CommandActive.h"
#include "Engine/CommandSolveCombat.h"
#include "Engine/CommandResolveCard.h"
#include "Engine/CommandTour.h"
#include "Engine/CommandVideMp.h"
#include <cmath>
#include <iostream>
#include <algorithm>

namespace Ai {

    Ia_Deep::Ia_Deep(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur) :
    Ia_Heuristic(state, moteur) {
    }

    void Ia_Deep::Think() {
        // si c'est le debut du tour
        if (currentState->GetPhase() == 0 || currentState->GetPhase() == 2 || currentState->GetPhase() == 4) {
            // on simplifie : on lance un terrain si on peux en lancer un
            PlayLand();
            DoBestAction();
            // on passe a la phase suivante

        } else if (currentState->GetPhase() == 1) {
            // on fait la liste des créatures avec lesquels c'est bien d'attaquer et on attaque
            Attaque();
            engine->Update();
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(2)));
            engine->Update();
        } else if (currentState->GetPhase() == 3) {
            // on fait la liste des créatures avec lesquels c'est bien d'attaquer
            Bloque();
            engine->Update();
            engine->AddCommand(std::shared_ptr<Engine::CommandSolveCombat>(new Engine::CommandSolveCombat(currentState)));
            engine->Update();
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(4)));
            engine->Update();
        }
    }

    void Ia_Deep::Attaque() {
        // prend la sortie maximale en admettant que l'on bloque au mieux
        // donc fait une liste de toute les configurations d'attaquants possible
        std::vector<std::shared_ptr<Etat::Creature> > list_attaquant;
        std::vector<bool> combiMax;
        int max = EvalState(), status = engine->HistoricSize();


        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature()
                    && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour()
                    && !currentState->GetBattlefield()[i]->GetIsTap())
                if (!std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetMalInvoc())
                    list_attaquant.push_back(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]));
        // cette boucle determine le nb de crea qui vont attaquer
        for (unsigned int i = 0; i < std::pow(2,list_attaquant.size()) ; i++) {
            std::vector<bool> tests = ExtractBool(i);
            for (unsigned int k = 0; k < tests.size(); k++)
                if (tests[k])
                    engine->AddCommand(std::shared_ptr<Engine::CommandAttack>(new Engine::CommandAttack(list_attaquant[k])));
            engine->Update();

            Bloque();
            int val = EvalState();
            if (val > max) {
                max = val;
                combiMax = tests;
            }
            Retour(status);
        }

        for (unsigned int k = 0; k < combiMax.size(); k++)
            if (combiMax[k])
                engine->AddCommand(std::shared_ptr<Engine::CommandAttack>(new Engine::CommandAttack(list_attaquant[k])));
        engine->Update();
    }

    void Ia_Deep::Bloque() {
        // fait une liste de tout les bloquage possible et prend la meilleur sortie
        // (celle où on meurt pas et où il y a le plus de mort chez eux et le moins chez nous
        std::vector<std::shared_ptr<Etat::Creature> > list_bloqueur;
        std::vector<int> list_compteur;
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature()
                    && !currentState->GetBattlefield()[i]->GetIsTap()
                    && currentState->GetBattlefield()[i]->GetIndJoueur() != currentState->GetJoueurTour()) {
                list_bloqueur.push_back(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]));
                list_compteur.push_back(-1);
            }
        int min = EvalState(), status = engine->HistoricSize();
        std::vector<int> bloque, bloqueur;
        bool continu = !list_compteur.empty();
        while (continu) {
            // declaration des bloqueurs
            for (unsigned int i = 0; i < list_bloqueur.size(); i++)
                if (list_compteur[i] != -1)
                    engine->AddCommand(std::shared_ptr<Engine::CommandBlock>(new Engine::CommandBlock(list_bloqueur[i], currentState->GetAttaquants()[list_compteur[i]])));
            engine->Update();

            // les tests
            engine->AddCommand(std::shared_ptr<Engine::CommandSolveCombat>(new Engine::CommandSolveCombat(currentState)));
            engine->Update();
            KillAll();
            int val = EvalState();
            if (currentState->GetJoueurs()[1 - currentState->GetJoueurTour()]->GetPv() > 0 && val < min) {
                // on "copie" la liste des compteurs dans la liste des bloqueurss et des bloques
                bloque.clear();
                bloqueur.clear();
                for (unsigned int i = 0; i < list_compteur.size(); i++)
                    if (list_compteur[i] != -1) {
                        bloqueur.push_back(i);
                        bloque.push_back(list_compteur[i]);
                    }
            }

            // test terminaison
            continu = false;
            for (unsigned int i = 0; i < list_compteur.size(); i++)
                if (list_compteur[i] != (int)currentState->GetAttaquants().size() - 1)
                    continu = true;

            // incrementation compteurs
            list_compteur[0]++;
            for (unsigned int i = 0; i < list_compteur.size(); i++)
                if (list_compteur[i] == (int)currentState->GetAttaquants().size()) {
                    list_compteur[i] = -1;
                    if (i < list_compteur.size() - 1)
                        list_compteur[i + 1]++;
                }
            // reset
            Retour(status);
        }

        for (unsigned int i = 0; i < bloqueur.size(); i++)
            engine->AddCommand(std::shared_ptr<Engine::CommandBlock>(new Engine::CommandBlock(list_bloqueur[bloqueur[i]], currentState->GetAttaquants()[bloque[i]])));
        engine->Update();
        engine->AddCommand(std::shared_ptr<Engine::CommandSolveCombat>(new Engine::CommandSolveCombat(currentState)));
        engine->Update();
    }

    std::vector<bool> Ia_Deep::ExtractBool(int val) {
        std::vector<bool> sortie;
        while(val)
        {
            sortie.push_back(val & 1);
            val >>=1;
        }
        std::reverse(sortie.begin(),sortie.end());
        return sortie;
    }

    void Ia_Deep::PlayLand() {
        if (currentState->GetJoueurTour() == currentState->GetPriority()) {
            int hist = engine->HistoricSize();
            std::shared_ptr<Etat::Carte> terrain;
            int max = EvalState();
            int def = max;
            bool smth = false;
            for (unsigned int i = 0; i < currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand().size(); i++)
                if (currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[i]->GetIsLand() && !currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetAJoueTerrain()) {
                    auto tampon = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[i];
                    engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(tampon)));
                    engine->Update();
                    engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(tampon, std::weak_ptr<Engine::Moteur>(engine))));
                    engine->Update();
                    DoBestAction();
                    int val = EvalState();
                    if (val >= max || smth == false) {
                        terrain = tampon;
                        max = val;
                        smth = true;
                    }
                    Retour(hist);
                }
            if (max >= def && smth) {
                engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(terrain)));
                engine->Update();
                engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(terrain, std::weak_ptr<Engine::Moteur>(engine))));
                engine->Update();
                //currentState->GetJoueurs()[currentState->GetJoueurTour()]->SetAJoueTerrain(true);
            }
        }
    }
}
