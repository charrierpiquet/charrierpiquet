#include "Declenchee.h"

namespace Etat
{
    Declenchee::Declenchee(int evnt, std::string motclef, int id, int prop):Capacite(motclef,2, id, prop)
    {
        event = evnt;
    }
    
    int Declenchee::GetEvent()
    {
        return event;
    }
    
};
