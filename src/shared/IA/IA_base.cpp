#include "IA_base.h"
#include "Engine/BlockCommand.h"
#include <iostream>
#include <ctime>
#include <Engine/CastCommand.h>
#include <Engine/LetPriorityCommand.h>
#include <Engine/AttackCommand.h>
#include <cstdlib>
#include <ctime>




namespace IA {

    IA_base::IA_base(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur) {
        currentState = state;
        engine = moteur;

    }

    void IA_base::Think() {
        std::srand(time(NULL));
        std::vector<std::shared_ptr<Etat::Carte> > MainJoueur;
        std::vector<std::shared_ptr<Etat::Carte> > NonLandMainJoueur;
        std::vector<std::shared_ptr<Etat::Carte> > Board;
        std::vector<std::shared_ptr<Etat::Carte> > TerrainsJoueur;
        std::vector<std::shared_ptr<Etat::Creature> > CreaturesJoueur;

        MainJoueur = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand();
        Board = currentState->GetBattlefield();
        unsigned int i = 0;
        
        for (i = 0; i < Board.size(); i++) //Récupération des listes de créatures et terrians controlés par le joueur
        {
            if ((Board[i]->GetIndJoueur() == currentState->GetJoueurTour()) && (Board[i]->GetIsCreature()))
                CreaturesJoueur.push_back(std::static_pointer_cast<Etat::Creature>(Board[i]));

            if ((Board[i]->GetIndJoueur() == currentState->GetJoueurTour()) && (Board[i]->GetIsLand()))
                TerrainsJoueur.push_back(Board[i]);
        }
        
        for (i = 0; i < MainJoueur.size(); i++) 
            if (!MainJoueur[i]->GetIsLand()) 
                NonLandMainJoueur.push_back(MainJoueur[i]);

        std::shared_ptr<Engine::LetPriorityCommand> Past(std::shared_ptr<Engine::LetPriorityCommand>(new Engine::LetPriorityCommand()));
        if (currentState->GetPile().empty())
        {
            // si on est dans la pre-combat main phase
            if (currentState->GetPhase()==0)
            {
                ajouer = false;
                // si c'est joueur dont c'est le tour qui a la priorite
                if (currentState->GetJoueurTour() == currentState->GetPriority())
                {
                    // si on peux jouer un terrain
                    if (!currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetAJoueTerrain())
                    {
                        bool passe = true;
                        for (i = 0; i < MainJoueur.size(); i++)
                            if (MainJoueur[i]->GetIsLand())
                            {
                                std::shared_ptr<Engine::CastCommand> Cast(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(MainJoueur[i], nullptr, nullptr)));
                                engine->AddCommand(Cast);
                                std::cout<<"on tente de poser un terrain"<<std::endl; 
                                passe = false;
                                break;
                            }
                        if (passe)
                        {
                            engine->AddCommand(Past);
                            std::cout<<"on passe"<<std::endl; 
                        }
                    }
                    else
                    {
                        engine->AddCommand(Past);
                        std::cout<<"on passe"<<std::endl; 
                    }
                }
                else
                {
                    engine->AddCommand(Past);
                    std::cout<<"on passe"<<std::endl; 
                }   
            }
            // si on est dans la post-combat main phase
            else if (currentState->GetPhase()==4)
            {
                // si c'est le joueur dont c'est le tour qui a la priorite
                if (currentState->GetJoueurTour() == currentState->GetPriority())
                {
                    // si il a des terrains
                    if (!TerrainsJoueur.empty())
                    {
                        // si ils sont degages
                        if (!TerrainsJoueur[0]->GetIsTap())
                            // on genere du mana avec nos terrains
                            for (i = 0; i < TerrainsJoueur.size(); i++) 
                            {
                                std::shared_ptr<Engine::CastCommand> TapLand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                                engine->AddCommand(TapLand);
                                std::cout<<"on tente de tap un terrain"<<std::endl;
                            }
                        else
                        {
                            //on tente de lancer une carte de notre main 
                            if (!NonLandMainJoueur.empty() && !ajouer)
                            {
                                int num = std::rand()%(NonLandMainJoueur.size());
                                std::shared_ptr<Engine::CastCommand> Cast(new Engine::CastCommand(NonLandMainJoueur[num], nullptr, nullptr));
                                engine->AddCommand(Cast);
                                std::cout<<"on tente de cast un truc"<<std::endl;
                                ajouer = true;
                            }
                            else
                            {
                                engine->AddCommand(Past);
                                std::cout<<"on passe"<<std::endl;
                            }
                        }
                    }
                }
                else
                {
                    engine->AddCommand(Past);
                    std::cout<<"on passe"<<std::endl;
                }
            }
            // si on est durant la phase de combat
            else if (currentState->GetPhase()==1)
            {
                // techniquement ça ce passe pas vraiment comme ça mais ça simplifie
                std::shared_ptr<Engine::AttackCommand> attaque(new Engine::AttackCommand());
                std::vector<std::shared_ptr<Etat::Creature> > attaquant;
                for (i = 0; i < CreaturesJoueur.size(); i++) 
                {
                    attaque->AddAttaquant(CreaturesJoueur[i]);
                    attaquant.push_back(CreaturesJoueur[i]);
                }
                engine->AddCommand(attaque);
                std::cout<<"on attaque avec tout ce qui peux attaquer"<<std::endl;
                
                std::shared_ptr<Engine::BlockCommand> bloque(new Engine::BlockCommand(attaquant));
                engine->AddCommand(bloque);
                std::cout<<"on ne bloque pas"<<std::endl;      
                engine->AddCommand(Past);engine->AddCommand(Past);engine->AddCommand(Past);
                std::cout<<"on passe trois fois pour quitter la phase de combat"<<std::endl;
            }
            else
            {
                engine->AddCommand(Past);
                std::cout<<"on passe"<<std::endl;
            }
            
        /*   
        switch (currentState->GetPhase()) {
            case 0:
            {
                for (i = 0; i < MainJoueur.size(); i++)
                {
                    if (MainJoueur[i]->GetIsLand())
                    {
                        std::shared_ptr<Engine::CastCommand> Cast(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(MainJoueur[i], nullptr, nullptr)));
                        engine->AddCommand(Cast);
                        std::cout<<"on tente de poser un terrain"<<std::endl;                        
                        break;
                    }
                }
                break;
            }

            case 1:
            {
                std::shared_ptr<Engine::AttackCommand> attaque(new Engine::AttackCommand());
                std::vector<std::shared_ptr<Etat::Creature> > attaquant;
                for (i = 0; i < CreaturesJoueur.size(); i++) 
                {
                    attaque->AddAttaquant(CreaturesJoueur[i]);
                    attaquant.push_back(CreaturesJoueur[i]);
                }
                engine->AddCommand(attaque);
                
                std::shared_ptr<Engine::BlockCommand> bloque(new Engine::BlockCommand(attaquant));
                engine->AddCommand(bloque);
                break;
            }

            case 4:
            {
                for (i = 0; i < TerrainsJoueur.size(); i++) {
                    std::shared_ptr<Engine::CastCommand> TapLand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                    engine->AddCommand(TapLand);
                    std::cout<<"on tente de tap un terrain"<<std::endl;
                }

                if (!NonLandMainJoueur.empty()) {
                    int num = std::rand()%(NonLandMainJoueur.size());
                    std::shared_ptr<Engine::CastCommand> Cast(new Engine::CastCommand(NonLandMainJoueur[num], nullptr, nullptr));
                    engine->AddCommand(Cast);
                    std::cout<<"on tente de cast un truc"<<std::endl;
                }        
                break;
            }
            default:
            {
                engine->AddCommand(Past);
                break;
            }
        }*/
        }
        else
        {
            engine->AddCommand(Past);
            std::cout<<"on passe"<<std::endl;
        }


    }



}
