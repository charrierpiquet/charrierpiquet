

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
                cout << "Tout c'est bien déroulé."<< endl;
        }
        else if ((string)argv[1] == "render")
        {
            std::shared_ptr<Etat::State> state( new Etat::State());
            Render::Rendu rendu(state,800,600);
           
            // creer l'etat
            
            // Creation d'une carte
				//création d'Iles (terrains de base)
			int identifiant = 0;
			cout<<identifiant<<endl;
            std::shared_ptr<Etat::Cout> coutIle (new Etat::Cout); cost->SetCost();
            std::vector<std::shared_ptr<Etat::Capacite> > capa;
            std::shared_ptr<Etat::Carte> Ile1(new Etat::Carte(true,true,false,false,"Ile",*coutIle,capa,identifiant++,0));
            state->AddCardBattlefield(*Ile1);				
            cout<<identifiant<<endl; //Jusqu'ici tout va bien
            std::shared_ptr<Etat::Carte> Ile2(new Etat::Carte(true,true,false,false,"Ile",*coutIle,capa,identifiant++,1));
            state->AddCardBattlefield(*Ile2);
            Ile2->SetIsTap(true);
            std::shared_ptr<Etat::Carte> Ile3(new Etat::Carte(true,true,false,false,"Ile",*coutIle,capa,identifiant++,0));
            state->GetJoueurs(0)->AddCardHand(Ile3);


				//Création d'Ours (Créatures de base)
			std::shared_ptr<Etat::Cout> coutOurs (new Etat::Cout); cost->SetCost(1,0,0,1,0,0,0,0,0);
            std::shared_ptr<Etat::Creature> Ours1(new Etat::Creature(2,2,false,"Ours",*coutOurs,,identifiant++,0));
            state->AddCardBattlefield(*Ours1);
            std::shared_ptr<Etat::Creature> Ours2(new Etat::Creature(2,2,false,"Ours",*coutOurs,,identifiant++,0));
            state->AddCardBattlefield(*Ours2);
            Ours2->SetIsTap(true);
            std::shared_ptr<Etat::Creature> Ours3(new Etat::Creature(2,2,false,"Ours",*coutOurs,,identifiant++,1));
            state->AddCardBattlefield(*Ours3);
            Ours3->SetCounter(2);
            std::shared_ptr<Etat::Creature> Ours4(new Etat::Creature(2,2,false,"Ours",*coutOurs,,identifiant++,0));
            state->GetJoueurs(0)->AddCardGraveyard(Ours4);
            std::shared_ptr<Etat::Creature> Ours5(new Etat::Creature(2,2,false,"Ours",*coutOurs,,identifiant++,1));
            state->GetJoueurs(1)->AddCardGraveyard(Ours5);


            
				
				
				
			//Rendu	
            sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement");
            window.setFramerateLimit(60);
            while (window.isOpen())
            {
                sf::Event event;
                while(window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    //tester le click;
                }
                window.clear(sf::Color::Black);
                rendu.Draw(window);
                window.display();
            }
            
        }
        else
            cout << "\"" << argv[1] << "\" n'est pas une commande implémentée."<<endl;
               
    }
    else
        cout << "trop d'arguments" <<endl;
        

    return 0;
}
