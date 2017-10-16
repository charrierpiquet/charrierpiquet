#include "Active.h"

namespace Etat
{
    Active::Active(Cout cout, std::string motclef, int id, int prop):Capacite(motclef,1, id, prop)
    {
        cost = cout;
    }
    
    Cout Active::GetCost() const
    {
        return cost;
    }
    
};