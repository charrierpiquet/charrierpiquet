

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
            std::shared_ptr<Etat::Cout> cost (new Etat::Cout); cost->SetCost();
            std::vector<std::shared_ptr<Etat::Capacite> > capa;
            std::shared_ptr<Etat::Carte> carte(new Etat::Carte(true,true,false,false,"ile",*cost,capa,1,0));
            state->AddCardBattlefield(*carte);
            
            sf::RenderWindow window(sf::VideoMode(800,600),"Sorcelerie, le Regroupement");
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
