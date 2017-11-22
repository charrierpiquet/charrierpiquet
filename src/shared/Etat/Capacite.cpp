#include "Capacite.h"
#include <iostream>
#include <string>

namespace Etat
{
    Capacite::Capacite(std::string motclef, int type, int id, int prop, std::string nom, bool target):Objet(true, id, prop, nom)
    {
        keyWord = motclef;
        needTarget = target;
        
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
    
    std::shared_ptr<Capacite> Capacite::Clone()
    {
        return std::shared_ptr<Capacite>(new Capacite(keyWord,categorie, this->GetIdObj(), this->GetIndJoueur(), this->GetName(), needTarget));
    }
    bool Capacite::GetNeedTarget()
    {
        return needTarget;
    }
  
    
};

