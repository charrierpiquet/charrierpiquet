#include "Ia_Heuristic.h"
#include "Engine/CommandUntap.h"
#include "Engine/CommandDraw.h"
#include "Engine/CommandPhase.h"
#include "Engine/CommandAttack.h"
#include "Engine/CommandSolveCombat.h"
#include "Engine/CommandPaye.h"
#include "Engine/CommandDie.h"
#include "Engine/CommandDiscard.h"
#include "Engine/CommandResolveCard.h"
#include "Engine/CommandResolveCapa.h"
#include "Engine/CommandCast.h"
#include "Engine/CommandActive.h"
#include "Engine/CommandTour.h"
#include "Engine/CommandClean.h"
#include "Engine/CommandPriority.h"
#include "Engine/CommandBlock.h"
#include <algorithm>
#include <ctime> 

static bool InvCompareCreaAtt(std::shared_ptr<Etat::Creature> a, std::shared_ptr<Etat::Creature> b) {
    return a->GetForce() > b->GetForce();
}

namespace Ai {

    Ia_Heuristic::Ia_Heuristic(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur) :
    Ia_Base(state, moteur) {

    }

    void Ia_Heuristic::Think() {
        // si c'est le debut du tour
        if (currentState->GetPhase() == 0) {
            DoBestAction();
        }// si c'est la phase de declaration des attaquants
        else if (currentState->GetPhase() == 1) {
            // on fait la liste des créatures avec lesquels c'est bien d'attaquer et on attaque
            Attaque();
            engine->Update();
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(2)));
            engine->Update();
        } else if (currentState->GetPhase() == 2) {
            // priorite on combat
            DoBestAction();
        } else if (currentState->GetPhase() == 3) {
            // on fait la liste des créatures avec lesquels c'est bien d'attaquer
            Bloque();
            engine->Update();
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(4)));
            engine->Update();
        } else if (currentState->GetPhase() == 4) {
            // on tente de faire un coup
            DoBestAction();
        }
    }

    int Ia_Heuristic::EvalState() {
        int status = engine->HistoricSize();
        int sortie = 0;
        // on vide la pile
        while (!currentState->GetPile().empty()) {
            if (currentState->GetPile()[currentState->GetPile().size() - 1]->GetIsCapacite())
                engine->AddCommand(std::shared_ptr<Engine::CommandResolveCapa>(new Engine::CommandResolveCapa(std::static_pointer_cast<Etat::Capacite>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
            else
                engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(std::static_pointer_cast<Etat::Carte>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
            engine->Update();
        }
        // on note
        int nb_crea = 0, offense = 0, defense = 0, carte_main = 0, nb_land = 0, nb_pv = 0, nb_autre = 0;
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++) {
            if (currentState->GetBattlefield()[i]->GetIsCreature()) {
                // si c'est toi qui est en train de regarder
                // on ne prend en compte que les creatures degages
                if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetIsTap()) {
                    if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority()) {
                        nb_crea++;
                        offense += std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce();
                        defense += std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                    } else {
                        nb_crea--;
                        offense -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                        defense -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce();
                    }
                } else {
                    if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority())
                        nb_autre++;
                    else
                        nb_autre--;
                }
            } else if (currentState->GetBattlefield()[i]->GetIsLand()) {
                if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority())
                    nb_land++;
                else
                    nb_land--;
            }
        }
        carte_main = currentState->GetJoueurs()[currentState->GetPriority()]->GetHand().size() - currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetHand().size();
        nb_pv = currentState->GetJoueurs()[currentState->GetPriority()]->GetPv() - currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetPv();
        //prise en compte des manapool pour la qtt de terrain
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetBlack();
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetBlue();
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetGreen();
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetMulti();
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetInc();

        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetBlack();
        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetBlue();
        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetGreen();
        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetMulti();
        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetInc();

        int k1 = 5, k2 = 3, k3 = 3, k4 = 1, k5 = 1, k6 = 1, k7 = 3; // voir pour changer les coefficients plus tard
        sortie = nb_crea * k1 + offense * k2 + defense * k3 + carte_main * k4 + nb_land * k5 + nb_pv * k6 + nb_autre*k7;
        // on reviens en arriere
        while (engine->HistoricSize() != status)
            engine->RollBack();
        // end
        return sortie;
    }

    void Ia_Heuristic::DoBestAction() {
        // on a besoin du max, de l'objet, de la cible, de la source
        int max = EvalState();
        int def = max;
        std::shared_ptr<Etat::Objet> obj;
        std::weak_ptr<Etat::Objet> cible;
        std::shared_ptr<Etat::Carte> src;
        int status = engine->HistoricSize();
        // pour chaque carte dans la main
        for (unsigned int i = 0; i < currentState->GetJoueurs()[currentState->GetPriority()]->GetHand().size(); i++) {
            // on tente de payer le cout
            if (TryCast(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetCost())) {
                // si ce ne sont pas des permanents
                if (!currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetIsPermanent()) {
                    bool needTarget = false;
                    for (unsigned int j = 0; j < currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetAbility().size(); j++)
                        if (currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetAbility()[j]->GetNeedTarget())
                            needTarget = true;
                    // si ils ont besoin de cible
                    if (needTarget) {
                        int hist = engine->HistoricSize();
                        // pour chaque carte sur la pile
                        for (unsigned int j = 0; j < currentState->GetPile().size(); j++) {
                            // on lance la carte avec celle la comme target
                            currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetAbility()[j]->SetTarget(std::weak_ptr<Etat::Objet>(currentState->GetPile()[j]));
                            engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i])));
                            engine->Update();
                            // on note
                            int val = EvalState();
                            if (val > max) {
                                max = val;
                                obj = currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i];
                                cible = std::weak_ptr<Etat::Objet>(currentState->GetPile()[j]);
                            }
                            // on reviens en arriere
                            Retour(hist);
                        }
                        // pour chaque carte sur le champ de bataille
                        for (unsigned int j = 0; j < currentState->GetBattlefield().size(); j++) {
                            // on lance la carte avec celle la comme target
                            currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetAbility()[j]->SetTarget(std::weak_ptr<Etat::Objet>(currentState->GetBattlefield()[j]));
                            engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i])));
                            engine->Update();
                            // on note
                            int val = EvalState();
                            if (val > max) {
                                max = val;
                                obj = currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i];
                                cible = std::weak_ptr<Etat::Objet>(currentState->GetBattlefield()[j]);
                            }
                            // on reviens en arriere
                            Retour(hist);
                        }
                    }// sinon si on est dans une phase ou on peux lancer la carte et que la pile est vide et que soit c'est un terrain et on a pas lancer de terrain soit c'est pas un terrain
                    else if ((currentState->GetPhase() == 0 || currentState->GetPhase() == 4) && currentState->GetPile().empty()
                            && ((currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetIsLand() && !currentState->GetJoueurs()[currentState->GetPriority()]->GetAJoueTerrain())
                            || !currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetIsLand())
                            && currentState->GetPriority() == currentState->GetJoueurTour()) {
                        // on lance la carte
                        engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i])));
                        engine->Update();
                        // on note
                        int val = EvalState();
                        if (val > max) {
                            max = val;
                            obj = currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i];
                            cible = std::weak_ptr<Etat::Objet>();
                        }
                    }
                } else {
                    // on lance la carte
                    engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i])));
                    engine->Update();
                    // on note
                    int val = EvalState();
                    if (val > max) {
                        max = val;
                        obj = currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i];
                    }
                }
                Retour(status);
            }
        }
        // pour chaque carte en jeu (sous notre controle & qui peux lancer une capa)
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority() && !currentState->GetBattlefield()[i]->GetIsTap()) {

                // pour chaque capacite de la carte
                for (unsigned int j = 0; j < currentState->GetBattlefield()[i]->GetAbility().size(); i++) {
                    // on tente de payer le cout
                    if (TryCast(currentState->GetBattlefield()[i]->GetAbility()[j]->GetCost())) {
                        //si on a besoin de cible
                        if (currentState->GetBattlefield()[i]->GetAbility()[j]->GetNeedTarget()) {
                            int hist = engine->HistoricSize();
                            for (unsigned int k = 0; k < currentState->GetPile().size(); k++) {
                                // on lance la carte avec celle la comme target
                                engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[j], std::weak_ptr<Etat::Objet>(currentState->GetPile()[k]))));
                                engine->Update();
                                // on note
                                int val = EvalState();
                                if (val > max) {
                                    max = val;
                                    src = currentState->GetBattlefield()[i];
                                    obj = currentState->GetBattlefield()[i]->GetAbility()[j];
                                    cible = std::weak_ptr<Etat::Objet>(currentState->GetPile()[k]);
                                }
                                // on reviens en arriere
                                Retour(hist);
                            }
                            // pour chaque carte sur le champ de bataille
                            for (unsigned int k = 0; k < currentState->GetBattlefield().size(); k++) {
                                // on lance la carte avec celle la comme target
                                engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[j], std::weak_ptr<Etat::Objet>(currentState->GetBattlefield()[k]))));
                                engine->Update();
                                // on note
                                int val = EvalState();
                                if (val > max) {
                                    max = val;
                                    src = currentState->GetBattlefield()[i];
                                    obj = currentState->GetBattlefield()[i]->GetAbility()[j];
                                    cible = std::weak_ptr<Etat::Objet>(currentState->GetBattlefield()[k]);
                                }
                                // on reviens en arriere
                                Retour(hist);
                            }
                        } else {
                            engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[j], std::weak_ptr<Etat::Objet>())));
                            engine->Update();
                            // on note
                            int val = EvalState();
                            if (val > max) {
                                max = val;
                                src = currentState->GetBattlefield()[i];
                                obj = currentState->GetBattlefield()[i]->GetAbility()[j];
                                cible = std::weak_ptr<Etat::Objet>();
                            }
                        }
                    }
                    Retour(status);
                }
            }

        // si une action est rentable
        if (max > def) {
            // on fait l'action correspondant au max
            if (obj->GetIsCapacite())
                engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(src, std::static_pointer_cast<Etat::Capacite>(obj), cible)));
            else {
                obj->SetTarget(cible);
                if (std::static_pointer_cast<Etat::Carte>(obj)->GetIsLand())
                    currentState->GetJoueurs()[currentState->GetPriority()]->SetAJoueTerrain(true);
                engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(std::static_pointer_cast<Etat::Carte>(obj))));
            }
            engine->Update();

        }// gestion priorite
        else {
            // si aucune action n'est rentable
            // on passe la priorite
            engine->AddCommand(std::shared_ptr<Engine::CommandPriority>(new Engine::CommandPriority(1 - currentState->GetPriority())));
            engine->Update();
            // si la pile est vide
            if (currentState->GetPile().empty()) {
                // si la priorite est egal au joueur dont c'est le tour
                if (currentState->GetPriority() == currentState->GetJoueurTour()) {
                    // si on est a la phase 4
                    if (currentState->GetPhase() == 4)
                        // fin tour
                        FinTour();
                        //sinon
                    else
                        // on passe a la phase suivante
                        engine->AddCommand(std::shared_ptr<Engine::CommandPriority>(new Engine::CommandPriority((currentState->GetPhase()+1) % 5)));
                    engine->Update();
                }
            }// sinon si le dernier objet lance a ete lance par le joueur qui a la priorite
            else if (currentState->GetPile()[currentState->GetPile().size() - 1]->GetIndJoueur() == currentState->GetPriority()) {
                // on resout l'objet
                if (currentState->GetPile()[currentState->GetPile().size() - 1]->GetIsCapacite())
                    engine->AddCommand(std::shared_ptr<Engine::CommandResolveCapa>(new Engine::CommandResolveCapa(std::static_pointer_cast<Etat::Capacite>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
                else
                    engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(std::static_pointer_cast<Etat::Carte>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
                engine->Update();
            }
        }
    }

    void Ia_Heuristic::Retour(int val) {
        if (val > engine->HistoricSize())
            while (engine->HistoricSize() != val)
                engine->RollBack();
    }

    // override TryCast pour qu'il engage aussi la mana

    bool Ia_Heuristic::TryCast(std::shared_ptr<Etat::Cout> cost) {
        // on admet qu'il n'existe que trois type de terrain (les terrains de base)
        // on admet que l'on commence avec la manapool vide
        bool canCast = false;
        int hist = engine->HistoricSize();
        int inc = cost->GetInc(), b = cost->GetBlack(), u = cost->GetBlue(), g = cost->GetGreen();

        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsLand() && !currentState->GetBattlefield()[i]->GetIsTap()) {
                if (b > 0 && currentState->GetBattlefield()[i]->GetName() == "Marais") {
                    engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                    b--;
                }
                if (u > 0 && currentState->GetBattlefield()[i]->GetName() == "Ile") {
                    engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                    u--;
                }
                if (g > 0 && currentState->GetBattlefield()[i]->GetName() == "Foret") {
                    engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                    g--;
                }
            }
        engine->Update();
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsLand() && !currentState->GetBattlefield()[i]->GetIsTap())
                if (i > 0) {
                    engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                    inc--;
                }
        engine->Update();

        int m1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetMulti();
        int i1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetInc();
        int b1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlack();
        int u1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlue();
        int g1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetGreen();

        engine->AddCommand(std::shared_ptr<Engine::CommandPaye>(new Engine::CommandPaye(cost)));
        engine->Update();

        int m2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetMulti();
        int i2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetInc();
        int b2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlack();
        int u2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlue();
        int g2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetGreen();

        canCast = m1 != m2 || i1 != i2 || b1 != b2 || u1 != u2 || g1 != g2;
        if (!canCast)
            Retour(hist);

        return canCast;
    }

    void Ia_Heuristic::FinTour() {
        // on tue les trucs qui doivent mourir
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature())
                if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance() <= 0)
                    engine->AddCommand(std::shared_ptr<Engine::CommandDie>(new Engine::CommandDie(currentState->GetBattlefield()[i])));
        engine->Update();
        // on clean le reste
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature())
                engine->AddCommand(std::shared_ptr<Engine::CommandClean>(new Engine::CommandClean(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]))));
        // on se defausse des cartes que l'on a en trop
        int nb = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand().size();
        for (int i = 6; i < nb; i++) // oblige de faire comme ça sinon ça merde
            engine->AddCommand(std::shared_ptr<Engine::CommandDiscard>(new Engine::CommandDiscard(currentState->GetJoueurTour())));

        engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(0)));
        engine->AddCommand(std::shared_ptr<Engine::CommandTour>(new Engine::CommandTour(1 - currentState->GetJoueurTour())));
        engine->Update();

        // c'est le debut du tour
        // on degage tout
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour())
                engine->AddCommand(std::shared_ptr<Engine::CommandUntap>(new Engine::CommandUntap(currentState->GetBattlefield()[i])));
        // on pioche
        engine->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(currentState->GetJoueurTour())));
        engine->Update();
    }

    void Ia_Heuristic::Attaque() {

        // si ta creature meurs pas et tue quelqu'un si elle est bloquee et que sa capacite n'est pas rentable
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature() && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour()) {
                int survie = std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                bool tue = true;

                for (unsigned int j = 0; j < currentState->GetBattlefield().size(); j++)
                    if (currentState->GetBattlefield()[j]->GetIsCreature() && currentState->GetBattlefield()[j]->GetIndJoueur() == 1 - currentState->GetJoueurTour()) {
                        survie -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[j])->GetForce();
                        if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce() < std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[j])->GetEndurance())
                            tue = false;
                    }

                if (tue && (!currentState->GetBattlefield()[i]->GetAbility().empty() || survie > 0))
                    engine->AddCommand(std::shared_ptr<Engine::CommandAttack>(new Engine::CommandAttack(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]))));
            }
    }

    void Ia_Heuristic::Bloque() {
        // bloquage extremement simplifie
        // theoriquement, on pourrait aussi bloquer avec une creature "inutile",
        // bloquer avec plusieurs creature sur une même creature, chercher a tuer a tout prix etc.
        int jDef = 1 - currentState->GetJoueurTour();

        std::vector<std::shared_ptr<Etat::Creature> > creaJDef;
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature() && currentState->GetBattlefield()[i]->GetIndJoueur() == jDef)
                creaJDef.push_back(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]));

        std::vector<std::shared_ptr<Etat::Creature> > attaquant = currentState->GetAttaquants();
        std::sort(attaquant.begin(), attaquant.end(), InvCompareCreaAtt); // ordonne selon attaque décroissante.
        // pour chaque crea attaquante
        for (unsigned int i = 0; i < attaquant.size(); i++)
            // si on peux la bloquer sans mourir
            for (unsigned int j = 0; j < creaJDef.size(); j++)
                if (creaJDef[j]->GetEndurance() > attaquant[i]->GetForce()) {
                    engine->AddCommand(std::shared_ptr<Engine::CommandBlock>(new Engine::CommandBlock(creaJDef[j],attaquant[i])));
                    creaJDef.erase(creaJDef.begin() + j);
                    break;
                }
    }
}

