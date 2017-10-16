#include "Capacite.h"
#include <iostream>
#include <string>

namespace Etat
{
    Capacite::Capacite(std::string motclef, int type, int id, int prop):Objet(true, id, prop)
    {
        keyWord = motclef;
        
        if (type >= 0 && type <= 2)
            categorie = type; // 0 = statique; 1 = activée; 2 = déclenchée
        else
            std::cout<<"erreur, ce type de capacite n'existe pas"<<std::endl;
    }  
    
    int Capacite::GetCategorie() const
    {
        return categorie;
    }
    
    std::string Capacite::GetKeyWord() const
    {
        return keyWord;
    }
  
    
};

