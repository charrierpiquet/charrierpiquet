#include "Declenchee.h"

namespace Etat
{
    Declenchee::Declenchee(int evnt, std::string motclef):Capacite(motclef,2)
    {
        event = evnt;
    }
    
    int Declenchee::GetEvent()
    {
        return event;
    }
    
};
