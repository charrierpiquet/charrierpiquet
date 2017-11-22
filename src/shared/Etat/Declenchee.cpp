#include "Declenchee.h"

namespace Etat
{
    Declenchee::Declenchee(int evnt, std::string motclef, int id, int prop, std::string nom):Capacite(motclef,2, id, prop, nom)
    {
        event = evnt;
    }
    
    int Declenchee::GetEvent()
    {
        return event;
    }
    
    std::shared_ptr<Declenchee> Declenchee::Clone()
    {
        return std::shared_ptr<Declenchee>(new Declenchee(event, this->GetKeyWord(), this->GetIdObj(), this->GetIndJoueur(), this->GetName()));
    }
    
};
