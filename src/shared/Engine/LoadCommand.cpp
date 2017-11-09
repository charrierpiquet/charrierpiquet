/*
 * LoadCommand.cpp
 * 
 * Copyright 2017 Charrier Piquet
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "LoadCommand.h"



namespace Engine
{
	LoadCommand::LoadCommand(std::string Deck1, std::string Deck2)
	{
		deck1 = Deck1;
		deck2 = Deck2;
	}
	
	void LoadCommand::Execute(std::shared_ptr<Etat::State> state)
	{
		std::string Type;
		std::string Nom;
		std::string Cout;
		std::string Force;
		std::string Endurance;
		std::string NbCapa;
		std::string Ability;
		std::string Texte;
		std::string Ligne;
		std::vector<std::shared_ptr<Etat::Capacite> > Capacites;
		int id=-1;
		int Joueur;
		int TailleDeck=0;
		
		
		for(Joueur=0;Joueur<(int)state->GetJoueurs().size();Joueur++)
		{
			std::ifstream FichierDeck;
			if(Joueur==0)
			{
				FichierDeck.open("/res/decks/" + deck1 + ".deck");
			}
			else
			{
				if(Joueur==1)
				{
					FichierDeck.open("/res/decks/" + deck2 + ".deck");
				}
				else
				{
					std::cout << "Beaucoup de joueurs ici" << std::endl;
					return;
				}
			}
			
			
			while(FichierDeck.peek()!=EOF)
			{
				TailleDeck++;
				std::getline(FichierDeck, Nom);
	
				std::ifstream Card("/res/cartes" + Nom + ".Carte");
				
				std::getline(Card, Type);
				std::getline(Card, Nom);
				std::getline(Card, Cout);
				std::getline(Card, Force);
				std::getline(Card, Endurance);
				std::getline(Card, NbCapa);
				for(int i=0;i<std::stoi(NbCapa);i++)
				{
					std::getline(Card, Ability);
					auto CostAbility = new Etat::Cout();
					CostAbility->SetCost(Ability[0],Ability[4],Ability[2],Ability[6],Ability[8],Ability[10],Ability[12],Ability[14],Ability[16]);
					Capacites.push_back(std::shared_ptr<Etat::Active>(new Etat::Active(*CostAbility,Ability.substr(18,Ability.size()-18),id++,Joueur,Ability.substr(18,Ability.size()-18))));
				}
				
				auto Cost = new Etat::Cout();
				Cost->SetCost(Cout[0],Cout[4],Cout[2],Cout[6],Cout[8],Cout[10],Cout[12],Cout[14],Cout[16]);
				if (std::strcmp(Type.data(), "creature")==0)
				{
					state->GetJoueurs()[Joueur]->AddCardLibrary(std::shared_ptr<Etat::Creature>(new Etat::Creature(std::stoi(Force),std::stoi(Endurance),false,Nom,*Cost,Capacites,id++,Joueur)));
				}
				else
				{
					state->GetJoueurs()[Joueur]->AddCardLibrary(std::shared_ptr<Etat::Carte>(new Etat::Carte(std::strcmp(Type.data(),"sort")!=0,std::strcmp(Type.data()	,"terrain")==0,std::strcmp(Type.data(),"creature")==0,0,Nom,*Cost,Capacites,id++,Joueur)));
				}
				
				Texte="";
				while(Card.peek()!=EOF)
				{
					getline(Card, Ligne);
					Texte=Texte + Ligne + "\n";
				}
				state->GetJoueurs()[Joueur]->GetLibrary()[TailleDeck]->SetOracle(Texte);			
				Card.close();
			}
			FichierDeck.close();
		}	
	}
}
