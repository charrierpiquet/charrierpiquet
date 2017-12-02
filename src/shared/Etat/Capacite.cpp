#include "Capacite.h"
#include "iostream"

namespace Etat
{
    Capacite::Capacite(std::shared_ptr<Cout> cout, std::string motclef, int id, int prop, std::string nom, bool target):Objet(true, id, prop, nom,cout)
    {
        keyWord = motclef;
        needTarget = target;
    }
    
    std::string Capacite::GetKeyWord() const
    {
        return keyWord;
    }
    bool Capacite::GetNeedTarget() const
    {
        return needTarget;
    }
  
};