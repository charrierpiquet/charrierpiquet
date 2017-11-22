#include "Active.h"

namespace Etat
{
    Active::Active(Cout cout, std::string motclef, int id, int prop, std::string nom):Capacite(motclef,1, id, prop, nom)
    {
        cost = cout;
    }
    
    Cout Active::GetCost() const
    {
        return cost;
    }
    std::shared_ptr<Active> Active::Clone()
    {
        return std::shared_ptr<Active>(new Active(cost, this->GetKeyWord(), this->GetIdObj(), this->GetIndJoueur(), this->GetName()));
    }
};