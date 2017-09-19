#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.hpp"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    if (argc == 2)
    {
        if ((string)argv[1] == "hello")
            cout << "Bonjour le monde !" << endl ;
        else
            cout << " \"" << argv[1] << "\" ne correspond à aucune fonctionnalité implémentée car l'orthografe " << endl ;
    }    
    else
    {
        Exemple exemple;
        exemple.setX(3);

        cout << "It works !" << endl;
    }
    return 0;
}
