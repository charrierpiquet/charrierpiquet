

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
using namespace Render;

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
            TestRender();
        }
        else if ((string)argv[1] == "engine")
        {
            int sortie = TestEngine();
            if (sortie != 0)
                cout << "Il y a des erreurs, voir sortie : "<< sortie << endl;
            else
                cout << "Tout s'est bien déroulé."<< endl;
        }
        else if ((string)argv[1] == "random_ai")
        {
            TestIARandom();
        }
        else if ((string)argv[1] == "heuristic_ai")
        {
            TestIAHeuristique();
        }
        else if ((string)argv[1] == "rollback")
        {
            TestRollback();
        }
        else if ((string)argv[1] == "deep_ai")
        {
            TestDeepIa();
        }
        else if ((string)argv[1] == "thread")
        {
            auto test = new TestMultiThread();
            test->testThread();
        }
        else if ((string)argv[1] == "play")
        {
            TestReplay();            
        }
        else
            cout << "\""<< argv[1] << "\"n'est pas une commande implémentée."<<endl;
               
    }
    else
        cout << "trop d'arguments"<<endl;
        

    return 0;
}
