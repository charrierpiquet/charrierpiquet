#include "Active.h"

namespace Etat
{
    Active::Active(Cout cout, std::string motclef):Capacite(motclef,1)
    {
        cost = cout;
    }
    
    Cout Active::GetCost()
    {
        return cost;
    }
    
};