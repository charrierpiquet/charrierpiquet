#include "IA_base.h"
#include <iostream>
#include <ctime>
#include <Engine/CastCommand.h>
#include <Engine/LetPriorityCommand.h>
#include <Engine/AttackCommand.h>
#include <cstdlib>
#include <ctime>




namespace IA
{
    IA_base::IA_base(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur)
    {
        currentState = state;
        engine = moteur;
        
    }
    
    
    void IA_base::Think()
    {
		srand(time(NULL));
		std::vector<std::shared_ptr<Etat::Carte> > MainJoueur;
		std::vector<std::shared_ptr<Etat::Carte> > NonLandMainJoueur;
		std::vector<std::shared_ptr<Etat::Carte> > Board;
		std::vector<std::shared_ptr<Etat::Carte> > TerrainsJoueur;
		std::vector<std::shared_ptr<Etat::Creature> > CreaturesJoueur;
		
		MainJoueur = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand();
		Board = currentState->GetBattlefield();
		int c=0;
		unsigned int i=0;
		for(i=0;i<Board.size();i++) //Récupération des listes de créatures et terrians controlés par le joueur
		{
			if ((Board[i]->GetIndJoueur() == currentState->GetJoueurTour()) && (Board[i]->GetIsCreature()))
			{
				CreaturesJoueur[c] = std::static_pointer_cast<Etat::Creature>(Board[i]);
				c++;
			}
			
			if ((Board[i]->GetIndJoueur() == currentState->GetJoueurTour()) && (Board[i]->GetIsLand()))
			{
				TerrainsJoueur[c] = Board[i];
				c++;
			}
		}
		c=0;
		for(i=0;i<MainJoueur.size();i++)
		{
			if (!MainJoueur[i]->GetIsLand())
			{
				NonLandMainJoueur[c]=MainJoueur[i];
				c++;
			}
		}
			
		std::shared_ptr<Engine::LetPriorityCommand> Past (std::shared_ptr<Engine::LetPriorityCommand>(new Engine::LetPriorityCommand()));
		switch(currentState->GetPhase())
		{
			case 0:
			{
			
				for(i=0;i<MainJoueur.size();i++)
				{
					if (MainJoueur[i]->GetIsLand())
					{
						std::shared_ptr<Engine::CastCommand> Cast (std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(MainJoueur[i],nullptr,nullptr)));
                        engine->AddCommand(Cast);
                        break;
					}
				}
				
				
				while(currentState->GetPhase()==0)
				{
					engine->AddCommand(Past);
				}
				break;
			}
			
			case 1:
			{
				std::shared_ptr<Engine::AttackCommand> attaque (std::shared_ptr<Engine::AttackCommand>(new Engine::AttackCommand()));
				for(i=0;i<CreaturesJoueur.size();i++)
				{
					attaque->AddAttaquant(CreaturesJoueur[i]);
				}
                engine->AddCommand(attaque);
                while(currentState->GetPhase()==1)
				{
					engine->AddCommand(Past);
				}
				break;
			}
			
			case 4:
			{
				for(i=0;i<TerrainsJoueur.size();i++)
				{
					std::shared_ptr<Engine::CastCommand> TapLand (std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0],TerrainsJoueur[i],nullptr)));
                    engine->AddCommand(TapLand);
				}
				
				
				if(NonLandMainJoueur.size()>0)
				{
					std::shared_ptr<Engine::CastCommand> Cast (std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(NonLandMainJoueur[rand()%(NonLandMainJoueur.size()-1)],nullptr,nullptr)));
					engine->AddCommand(Cast);
				}
				
				while(currentState->GetPhase()==4)
				{
					engine->AddCommand(Past);
				}
				break;
			}
			default:
			{
				engine->AddCommand(Past);
				break;
			}
		}
					
       
    }
    
    
    
}
