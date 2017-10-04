#include "Capacite.h"

namespace Etat
{
    Capacite::Capacite(std::string motclef, int type)
    {
        keyWord = motclef;
        if (type >= 0 && type =< 2)
            categorie = type; // 0 = statique; 1 = activée; 2 = déclenchée
        else
            std::cout<<"erreur, ce type de capacite n'existe pas"<<std::endl;
    }  
    
    int Capacite::GetCategorie()
    {
        return categorie;
    }
    
    std::string Capacite::GetKeyWord()
    {
        return keyWord;
    }
  
    
};

