#include "Ia_Base.h"
#include "Engine/CommandUntap.h"
#include "Engine/CommandDraw.h"
#include "Engine/CommandPhase.h"
#include "Engine/CommandAttack.h"
#include "Engine/CommandSolveCombat.h"
#include "Engine/CommandPriority.h"
#include "Engine/CommandPaye.h"
#include "Engine/CommandDie.h"
#include "Engine/CommandDiscard.h"
#include "Engine/CommandResolveCard.h"
#include "Engine/CommandResolveCapa.h"
#include "Engine/CommandCast.h"
#include "Engine/CommandActive.h"
#include "Engine/CommandTour.h"
#include "Engine/CommandClean.h"
#include <algorithm>
#include <ctime>
#include <iostream>

namespace Ai {

    Ia_Base::Ia_Base(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur) {
        currentState = state;
        engine = moteur;
    }

    void Ia_Base::Think() {
        // si c'est le debut du tour
        if (currentState->GetPhase() == 0) {
            engine->AddCommand(std::shared_ptr<Engine::CommandPriority>(new Engine::CommandPriority(currentState->GetJoueurTour())));
            engine->Update();
            // c'est le debut du tour
            // on degage tout
            std::cout<<"\tupkeep"<<std::endl;
            for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
                if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour())
                    engine->AddCommand(std::shared_ptr<Engine::CommandUntap>(new Engine::CommandUntap(currentState->GetBattlefield()[i])));
            // on pioche
            engine->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(currentState->GetJoueurTour())));
            engine->Update();
            std::cout<<"\trecherche terrain"<<std::endl;
            // on cherche un terrain dans notre main
            for (unsigned int i = 0; i < currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand().size(); i++)
                if (currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[i]->GetIsLand()) {
                    // un terrain n'ayant pas de cout, on cast le terrain
                    engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[i])));
                    // techniquement, un terrain ne passe pas par la pile donc on resout le terrain
                    engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[i], std::weak_ptr<Engine::Moteur>(engine))));
                    // on a jouer un terrain on devrait s'occuper du a jouer un terrain mais vue l'utilité ici on s'abstient
                    break;
                }
            std::cout<<"\ton passe"<<std::endl;
            // on passe a la phase suivante
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(1)));
            engine->Update();
            
        }// si c'est la phase de declaration des attaquants
        else if (currentState->GetPhase() == 1) {
            std::cout<<"\tattaque"<<std::endl;
            // on declare toute nos creatures comme attaquante
            for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
                if (currentState->GetBattlefield()[i]->GetIsCreature() && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour())
                    engine->AddCommand(std::shared_ptr<Engine::CommandAttack>(new Engine::CommandAttack(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]))));
            engine->Update();
            std::cout<<"\tresolution"<<std::endl;
            // on finis le combat et on passe a la main phase post-combat
            //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
            engine->AddCommand(std::shared_ptr<Engine::CommandSolveCombat>(new Engine::CommandSolveCombat()));
            engine->Update();
            //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
            std::cout<<"\ton passe"<<std::endl;
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(4)));
            engine->Update();
            //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
        } else if (currentState->GetPhase() == 4) {
            // on engage tout nos terrains pour la mana
            std::cout<<"\ton depense"<<std::endl;
            for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
                if (currentState->GetBattlefield()[i]->GetIsLand() && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour())
                    if(!currentState->GetBattlefield()[i]->GetAbility().empty())
                    {
                        engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                        engine->AddCommand(std::shared_ptr<Engine::CommandResolveCapa>(new Engine::CommandResolveCapa(currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Engine::Moteur>(engine))));
                    }
            
                engine->Update();
            std::cout<<"\ton joue"<<std::endl;
            // on choisi une carte au hasard dans sa main
            std::srand(unsigned ( std::time(0)));
            int k = std::rand() % currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand().size();
            // si ce n'est pas un terrain
            if (!currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[k]->GetIsLand()) {
                // si on peux la lancer
                std::cout<<"\t\t"<<currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[k]->GetName()<<"\t"<<currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[k]->GetIsPermanent()<<std::endl;
                bool test = TryCast(currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[k]->GetCost());
                std::cout<<"\t\tsortie = "<<test<<std::endl;
                if (test) {
                    //std::cout<<"on arrive la"<<std::endl;
                    // on la lance (on admet que ce qu'on lancera n'a pas besoin de cible)
                    std::cout<<"\t\tOn le lance\t";
                    engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[k])));
                    engine->Update();
                    std::cout<<"On le resout";
                    // on la resout (osef la priorite)
                    engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(std::static_pointer_cast<Etat::Carte>(currentState->GetPile()[currentState->GetPile().size()-1]), std::weak_ptr<Engine::Moteur>(engine))));
                    std::cout<<"\tCommande cree";
                    engine->Update();
                    std::cout<<"\tCommande resolu"<<std::endl;
                }
                else
                    std::cout<<"\t\tNOPE"<<std::endl;
            }
            std::cout<<"\ton vide la manapool"<<std::endl;
            // on vide les manapool
            for (unsigned int i = 0 ; i < currentState->GetJoueurs().size() ; i++ )
            {
                currentState->GetJoueurs()[i]->GetManaPool()->SetMulti(0);
                currentState->GetJoueurs()[i]->GetManaPool()->SetInc(0);
                currentState->GetJoueurs()[i]->GetManaPool()->SetBlack(0);
                currentState->GetJoueurs()[i]->GetManaPool()->SetBlue(0);
                currentState->GetJoueurs()[i]->GetManaPool()->SetGreen(0);
            }
            std::cout<<"\ton tue "<<std::endl;
            // on tue les trucs qui doivent mourir
            for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
                if (currentState->GetBattlefield()[i]->GetIsCreature())
                    if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance() <= 0)
                        engine->AddCommand(std::shared_ptr<Engine::CommandDie>(new Engine::CommandDie(currentState->GetBattlefield()[i])));
            engine->Update();
            // on clean le reste
            std::cout<<"\ton clean"<<std::endl;
            for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
                if (currentState->GetBattlefield()[i]->GetIsCreature())
                    engine->AddCommand(std::shared_ptr<Engine::CommandClean>(new Engine::CommandClean(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]))));
            // on se defausse des cartes que l'on a en trop
            std::cout<<"\ton se defausse"<<std::endl;
            int nb = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand().size();
            for (int i = 6; i < nb; i++) // oblige de faire comme ça sinon ça merde
                engine->AddCommand(std::shared_ptr<Engine::CommandDiscard>(new Engine::CommandDiscard(currentState->GetJoueurTour())));
            std::cout<<"\ton passe"<<std::endl;
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(0)));
            engine->AddCommand(std::shared_ptr<Engine::CommandTour>(new Engine::CommandTour(1 - currentState->GetJoueurTour())));
            engine->Update();
        }
    }

    bool Ia_Base::TryCast(std::shared_ptr<Etat::Cout> cost) {
        //std::cout<<currentState->GetJoueurTour()<<" ";
        std::cout<<"\t\t\ton tente de le lancer"<<std::endl;
        int m1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetMulti();
        int i1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetInc();
        int b1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlack();
        int u1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlue();
        int g1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetGreen();
//std::cout<<"ici"<<std::endl;
        engine->AddCommand(std::shared_ptr<Engine::CommandPaye>(new Engine::CommandPaye(cost)));
        std::cout<<"\t\t\ton creer la commande"<<std::endl;
        engine->Update();
        std::cout<<"\t\t\ton paye"<<std::endl;
//std::cout<<"la"<<std::endl;
        int m2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetMulti();
        int i2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetInc();
        int b2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlack();
        int u2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlue();
        int g2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetGreen();
        std::cout<<"\t\t\ton recupere les valeurs"<<std::endl;
        bool sortie = m1 != m2 || i1 != i2 || b1 != b2 || u1 != u2 || g1 != g2;
        std::cout<<"\t\t\tsortie  = "<<sortie<<std::endl;
        //std::cout<<sortie<<std::endl;
        if (!sortie)
        {
            std::cout<<"\t\t\ton tente d'annuller"<<std::endl;
            engine->RollBack();
            std::cout<<"\t\t\ton annule"<<std::endl;
        }
        std::cout<<"\t\t\tWut ?!"<<std::endl;
        return sortie;
    }

}