

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "Etat.h"
#include "Test.h"
#include "Render.h"
#include <iostream>

using namespace std;
using namespace Etat;
using namespace Test;

// c'est quoi ces problemes de memoire ?!

int main(int argc,char* argv[]) 
{
    //Exemple exemple;
    //exemple.setX(53);
    if (argc == 1 )
        cout << "It works !"<< endl;
    else if (argc == 2 )
    {
        if ((string)argv[1] == "hello")
            cout << "Bonjour le monde !"<< endl;
        else if ((string)argv[1] == "state")
        {                
            int sortie = TestEtat();   
            if (sortie != 0)
                cout << "Il y a des erreurs, voir sortie : "<< sortie << endl;
            else
                cout << "Tout s'est bien déroulé."<< endl;
        }
        else if ((string)argv[1] == "render")
        {
            std::shared_ptr<Etat::State> state( new Etat::State());
            Render::Rendu rendu(state,1200,900);
            bool needActu =true;
           
            // creer l'etat
            
            // Creation d'une carte
            //création d'Iles (terrains de base)
            int identifiant = 0;
            
            shared_ptr<Cout> coutTerrain(new Cout);
            coutTerrain->SetCost();

            vector<shared_ptr<Capacite> > capa;
            
            shared_ptr<Carte> Foret1(new Carte(true,true,false,false,"Foret",*coutTerrain,capa,identifiant++,0));
            Foret1->SetOracle("ceci est une foret \ntap : ajoutez (G) a votre reserve\nune foret est un terrain\nun terrain est incolore");
            state->AddCardBattlefield(*Foret1);
            
            shared_ptr<Carte> Marais1(new Carte(true,true,false,false,"Marais",*coutTerrain,capa,identifiant++,0));
            Marais1->SetOracle("ceci est un marais \ntap : ajoutez (B) a votre reserve\nun marais est un terrain\nun terrain est incolore");
            state->AddCardBattlefield(*Marais1);
            
            shared_ptr<Carte> Ile2(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,1));
            Ile2->SetIsTap(true);
            Ile2->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
            state->AddCardBattlefield(*Ile2);
            
            shared_ptr<Carte> Ile3(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,0));
            Ile3->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
            state->GetJoueurs()[0]->AddCardHand(*Ile3);
            
            shared_ptr<Carte> Ile4(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,1));
            Ile4->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
            state->GetJoueurs()[1]->AddCardGraveyard(*Ile4);

            //Création d'Ours (Créatures de base)
            shared_ptr<Cout> coutOurs (new Cout); coutOurs->SetCost(1,0,0,1);
            shared_ptr<Creature> Ours1(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            Ours1->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force et une endurance de 2\nun Ours est vert");
            Ours1->SetIsTap(true);
            state->AddCardBattlefield(*Ours1);

            shared_ptr<Creature> Ours2(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            Ours2->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force et une endurance de 2\nun Ours est vert");
            state->AddCardBattlefield(*Ours2);
            
            shared_ptr<Creature> Ours3(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,1));
            Ours3->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force et une endurance de 2\nun Ours est vert\ncet ours a 2 marqueurs");
            Ours3->SetIsTap(true);
            Ours3->SetCounter(2);
            state->AddCardBattlefield(*Ours3);       
            
            shared_ptr<Creature> Ours4(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            Ours4->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force et une endurance de 2\nun Ours est vert\ncet ours a 1 blessure");
            Ours4->SetBlessure(1);
            state->GetJoueurs()[0]->AddCardGraveyard(*Ours4);
            
            shared_ptr<Creature> Ours5(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,1));
            Ours5->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force et une endurance de 2\nun Ours est vert\ncet ours a un bonus de -1");
            Ours5->SetBonusEOT(-1);
            state->GetJoueurs()[1]->AddCardGraveyard(*Ours5);
            
            shared_ptr<Creature> Ours6(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            Ours6->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force et une endurance de 2\nun Ours est vert");
            Ours6->SetIsTap(true);
            state->AddCardBattlefield(*Ours6);

            shared_ptr<Creature> Ours7(new Creature(2, 2, false, "Ours", *coutOurs, capa, identifiant++, 0));
            Ours7->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force et une endurance de 2\nun Ours est vert");
            state->AddCardBattlefield(*Ours7);

            shared_ptr<Creature> Ours8(new Creature(2, 2, false, "Ours", *coutOurs, capa, identifiant++, 0));
            Ours8->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force et une endurance de 2\nun Ours est vert");
            state->AddCardBattlefield(*Ours8);
            
            //Rendu	
            sf::RenderWindow window(sf::VideoMode(1200,900),"Sorcellerie, le Regroupement",sf::Style::Close);
            window.setFramerateLimit(60);
            while (window.isOpen())
            {
                sf::Event event;
                
                while (window.pollEvent(event))
                {
                    needActu = true;
                    if (event.type == sf::Event::Closed)
                        window.close();
                    //tester le click;
                    if (event.type == sf::Event::MouseButtonPressed)
                        if (event.mouseButton.button == sf::Mouse::Left)
                            rendu.Click(event.mouseButton.x,event.mouseButton.y);
                }
                
                if (needActu)
                {
                window.clear(sf::Color::Black);
                rendu.Draw(window);
                
                window.display();
                needActu = false;
                }
            }
            cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        }
        else
            cout << "\""<< argv[1] << "\"n'est pas une commande implémentée."<<endl;
               
    }
    else
        cout << "trop d'arguments"<<endl;
        

    return 0;
}
