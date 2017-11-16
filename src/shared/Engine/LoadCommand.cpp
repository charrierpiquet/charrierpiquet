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
#include <algorithm>
#include <ctime> 
#include <cstdlib>
#include "LoadCommand.h"
#include "Etat/Active.h"
#include "Etat/Creature.h"



namespace Engine
{
    LoadCommand::LoadCommand(std::string Deck1, std::string Deck2)
    {
        deck1 = Deck1;
        deck2 = Deck2;
    }
	
    void LoadCommand::Execute(std::shared_ptr<Etat::State> state)
    {
        
        std::string Type ="";
        std::string Nom="";
        std::string Cout="";
        std::string Force="";
        std::string Endurance="";
        std::string NbCapa="";
        std::string Ability="";
        std::string Texte="";
        std::string Ligne="";
        std::vector<std::shared_ptr<Etat::Capacite> > Capacites;
        int id=-1;
        int Joueur;
        
        std::vector<std::shared_ptr<Etat::Carte> > list_deck1;
        std::vector<std::shared_ptr<Etat::Carte> > list_deck2;
                
        for(Joueur=0;Joueur<(int)state->GetJoueurs().size();Joueur++)
        {
            int TailleDeck=0;
            std::ifstream FichierDeck;
            if(Joueur==0)
            {
                FichierDeck.open("./res/" + deck1 + ".deck");
                std::cout<<"chargement deck 1 ..."<<std::endl;
            }
            else
            {
                if(Joueur==1)
                {
                    FichierDeck.open("./res/" + deck2 + ".deck");
                    std::cout<<"chargement deck 2 ..."<<std::endl;
                }
                else
                {
                    std::cout << "Beaucoup de joueurs ici" << std::endl;
                    return;
                }
            }
            if (!FichierDeck)
                std::cout<<"impossible d'ouvrir le deck"<<std::endl;
            
            while(FichierDeck.peek()!= EOF)
            {
                TailleDeck++;
                std::getline(FichierDeck, Nom);
                //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                Nom.erase(Nom.end()-1);
                //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                //std::cout<<"."<<Nom<<"."<<std::endl;
                //std::cout<<Nom.size()<<std::endl;
                std::ifstream Card("./res/cartes/" + Nom + ".carte");
                //std::ifstream Card("./res/cartes/Ours.carte");
                if (!Card)
                    std::cout<<"impossible d'ouvrir la carte "<<Nom<<std::endl;
                else
                {
                std::getline(Card, Type);       //Type.erase(Type.end()-1);
                std::getline(Card, Nom);        //Nom.erase(Nom.end()-1);
                std::getline(Card, Cout);       //Cout.erase(Cout.end()-1);
                std::getline(Card, Force);      //Force.erase(Force.end()-1);
                std::getline(Card, Endurance);  //Endurance.erase(Endurance.end()-1);
                std::getline(Card, NbCapa);     //NbCapa.erase(NbCapa.end()-1);                
                
                int k = std::stoi(NbCapa,nullptr,0), f=std::stoi(Force,nullptr,0),e=std::stoi(Endurance,nullptr,0);
                //std::cout<<Type<<"."<<std::endl<<Nom<<"."<<std::endl<<f<<"."<<std::endl<<e<<"."<<std::endl<<k<<"."<<std::endl;
                Capacites.clear();
                if (k != 0)     
                    for(int i=0;i<k;i++)
                    {
                        std::getline(Card, Ability);
                        auto CostAbility = new Etat::Cout();
                        CostAbility->SetCost(Ability[0]-'0',Ability[4]-'0',Ability[2]-'0',Ability[6]-'0');                  
                        Capacites.push_back(std::shared_ptr<Etat::Active>(new Etat::Active(*CostAbility,Ability.substr(18,Ability.size()-18),id++,Joueur,Ability.substr(18,Ability.size()-18))));
                    }
                
                std::shared_ptr<Etat::Cout> Cost(new Etat::Cout());
                Cost->SetCost(Cout[0]-'0',Cout[4]-'0',Cout[2]-'0',Cout[6]-'0');
                if (std::strcmp(Type.data(), "creature")==0)
                {
                    if (Joueur == 0)
                        list_deck1.push_back(std::shared_ptr<Etat::Creature>(new Etat::Creature(f,e,false,Nom,*Cost,Capacites,id++,Joueur)));
                    else
                        list_deck2.push_back(std::shared_ptr<Etat::Creature>(new Etat::Creature(f,e,false,Nom,*Cost,Capacites,id++,Joueur)));
                }
                else
                {
                    if (Joueur == 0)
                        list_deck1.push_back(std::shared_ptr<Etat::Carte>(new Etat::Carte(std::strcmp(Type.data(),"sort")!=0,std::strcmp(Type.data()	,"terrain")==0,std::strcmp(Type.data(),"creature")==0,0,Nom,*Cost,Capacites,id++,Joueur)));
                    else 
                        list_deck2.push_back(std::shared_ptr<Etat::Carte>(new Etat::Carte(std::strcmp(Type.data(),"sort")!=0,std::strcmp(Type.data()	,"terrain")==0,std::strcmp(Type.data(),"creature")==0,0,Nom,*Cost,Capacites,id++,Joueur)));
                }
                
                Texte="";
                while(Card.peek()!=EOF)
                {
                    getline(Card, Ligne);
                    Texte=Texte + Ligne + "\n";
                }
                //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                //std::cout<<state->GetJoueurs().size()<<" "<<Joueur<<std::endl;
                if (Joueur == 0)
                    list_deck1[TailleDeck-1]->SetOracle(Texte);
                else
                    list_deck2[TailleDeck-1]->SetOracle(Texte);
                //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                Card.close();
                //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                }
            }
            FichierDeck.close();
        }
        
        std::srand ( unsigned ( std::time(0) ) );
            while (!list_deck1.empty())
            {
                int k = std::rand()%list_deck1.size();
                state->GetJoueurs()[0]->AddCardLibrary(list_deck1[k]);
                list_deck1.erase(list_deck1.begin()+k);
            }
        while (!list_deck2.empty())
            {
                int k = std::rand()%list_deck2.size();
                state->GetJoueurs()[1]->AddCardLibrary(list_deck2[k]);
                list_deck2.erase(list_deck2.begin()+k);
            }
        /*int size = std::min(state->GetJoueurs()[0]->GetLibrary().size(), state->GetJoueurs()[1]->GetLibrary().size());
        for (int i = 0; i < size; i++)
        {
            using std::swap;
            int rand1 = std::rand()%(size-1), rand2 =std::rand()%(size-1);
            swap(state->GetJoueurs()[0]->GetLibrary()[i],state->GetJoueurs()[0]->GetLibrary()[rand1]);
            swap(state->GetJoueurs()[1]->GetLibrary()[i],state->GetJoueurs()[1]->GetLibrary()[rand2]);
            std::cout<<rand1<<" "<<rand2<<std::endl;
        }
        
        for (int i = 0; i<size;i++)
            std::cout<<state->GetJoueurs()[0]->GetLibrary()[i]->GetName()<<std::endl;*/
        //std::random_shuffle(state->GetJoueurs()[0]->GetLibrary().begin(),state->GetJoueurs()[0]->GetLibrary().end());
        //std::random_shuffle(state->GetJoueurs()[1]->GetLibrary().begin(),state->GetJoueurs()[1]->GetLibrary().end());
        //std::cout<<"coucou c'est moi !"<<std::endl;
    }
}
