#include "Active.h"
#include "iostream"

namespace Etat
{
    Active::Active(std::shared_ptr<Cout> cout, std::string motclef, int id, int prop, std::string nom, bool target):Capacite(motclef,1, id, prop, nom, target)
    {
        cost = cout;
    }
    
    std::shared_ptr<Cout> Active::GetCost() const
    {
        return cost;
    }
    std::shared_ptr<Active> Active::Clone()
    {
        std::shared_ptr<Cout> new_cout;
        new_cout->SetCost(cost->GetInc(),cost->GetBlue(),cost->GetBlack(),cost->GetGreen(),0,cost->GetLife());
        std::shared_ptr<Active> clone(new Active(new_cout, this->GetKeyWord(), this->GetIdObj(), this->GetIndJoueur(), this->GetName(),this->GetNeedTarget()));
        std::cout<<"\t cout de base : "<<cost->GetBlack()<<" "<<cost->GetBlue()<<" "<<cost->GetGreen()<<" "<<cost->GetInc()<<std::endl;
        std::cout<<"\t copie du cout : "<<clone->GetCost()->GetBlack()<<" "<<clone->GetCost()->GetBlue()<<" "<<clone->GetCost()->GetGreen()<<" "<<clone->GetCost()->GetInc()<<std::endl;
        return clone;
    }
};