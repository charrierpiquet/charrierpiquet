

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "Etat.h"
#include "TestEtat.h"
#include <iostream>

using namespace std;
using namespace Etat;

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
            int sortie = testEtat();   
            if (sortie != 0)
                cout << "Il y a des erreurs, voir sortie : " << sortie <<endl;
            else
                cout << "Tout c'est bien déroulé."<< endl;
        }
        else
            cout << "\"" << argv[1] << "\" n'est pas une commande implémentée."<<endl;
                
    
        
//        if ((string)argv[1] == "hello")
//            cout << "Bonjour le monde !"<< endl;
//        else
//            cout << "\"" << argv[1] << "\" n'est pas une commande implémentée."<<endl;
    }
    else
        cout << "trop d'arguments" <<endl;
        

    return 0;
}
