

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

int main(int argc,char* argv[]) 
{
    //Exemple exemple;
    //exemple.setX(53);
    if (argc == 1 )
        cout << "It works !" << endl;
    else if (argc == 2 )
    {
        if ((string)argv[1] == "hello")
            cout << "Bonjour le monde !"<< endl;
        else if ((string)argv[1] == "state")
        {                
            int sortie = TestEtat();   
            if (sortie != 0)
                cout << "Il y a des erreurs, voir sortie : " << sortie << endl;
            else
                cout << "Tout s'est bien déroulé."<< endl;
        }
        else if ((string)argv[1] == "render")
        {
            std::shared_ptr<Etat::State> state( new Etat::State());
            Render::Rendu rendu(state,800,600);
            bool needActu =true;
           
            // creer l'etat
            
            // Creation d'une carte
            //création d'Iles (terrains de base)
            int identifiant = 0;
            
            shared_ptr<Cout> coutTerrain(new Cout);
            coutTerrain->SetCost();

            vector<shared_ptr<Capacite> > capa;
            
            shared_ptr<Carte> Foret1(new Carte(true,true,false,false,"Foret",*coutTerrain,capa,identifiant++,0));
            state->AddCardBattlefield(*Foret1);
            shared_ptr<Carte> Marais1(new Carte(true,true,false,false,"Marais",*coutTerrain,capa,identifiant++,0));
            state->AddCardBattlefield(*Marais1);
            
            shared_ptr<Carte> Ile2(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,1));
            Ile2->SetIsTap(true);
            state->AddCardBattlefield(*Ile2);
            
            shared_ptr<Carte> Ile3(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,0));
            state->GetJoueurs()[0]->AddCardHand(*Ile3);
            shared_ptr<Carte> Ile4(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,1));
            state->GetJoueurs()[1]->AddCardGraveyard(*Ile4);

            //Création d'Ours (Créatures de base)
            shared_ptr<Cout> coutOurs (new Cout); coutOurs->SetCost(1,0,0,1);
            shared_ptr<Creature> Ours1(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            Ours1->SetIsTap(true);
            state->AddCardBattlefield(*Ours1);

            shared_ptr<Creature> Ours2(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            state->AddCardBattlefield(*Ours2);
            
            shared_ptr<Creature> Ours3(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,1));
            Ours3->SetIsTap(true);
            Ours3->SetCounter(2);
            state->AddCardBattlefield(*Ours3);       
            
            shared_ptr<Creature> Ours4(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            state->GetJoueurs()[0]->AddCardGraveyard(*Ours4);
            
            shared_ptr<Creature> Ours5(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,1));
            state->GetJoueurs()[1]->AddCardGraveyard(*Ours5);
            
            shared_ptr<Creature> Ours6(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            Ours6->SetIsTap(true);
            state->AddCardBattlefield(*Ours6);
            
            shared_ptr<Creature> Ours7(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            state->AddCardBattlefield(*Ours7);
            
            shared_ptr<Creature> Ours8(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
            state->AddCardBattlefield(*Ours8);
            
            //Rendu	
            sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
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
            
        }
        else
            cout << "\"" << argv[1] << "\" n'est pas une commande implémentée."<<endl;
               
    }
    else
        cout << "trop d'arguments" <<endl;
        

    return 0;
}
