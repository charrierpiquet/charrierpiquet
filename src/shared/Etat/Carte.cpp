#include "Carte.h"
#include "iostream"
namespace Etat
{
    Carte::Carte(bool permanent,bool land,bool creature,bool token,
            std::string nom,std::shared_ptr<Cout> cout, std::vector<std::shared_ptr<Capacite> > capa, int id, int prop):
    Objet(false, id, prop, nom), cost(cout),ability(capa)
    {
        isPermanent = permanent;
        isLand = land;
        isCreature = creature;
        isToken = token;       
        
        counters =0;
        isTap = false;
        
    }
    
    std::shared_ptr<Cout> Carte::GetCost() const
    {
        return cost;
    }
    
    bool Carte::GetIsLand() const
    {
        return isLand;
    }
    
    bool Carte::GetIsPermanent() const
    {
        return isPermanent;
    }
    
    bool Carte::GetIsCreature() const
    {
        return isCreature;
    }
    
    bool Carte::GetIsToken() const
    {
        return isToken;
    }
     
    bool Carte::GetIsTap() const
    {
        return isTap;
    }
    
    int Carte::GetCounter() const
    {
        return counters;
    }
    
    std::vector<std::shared_ptr<Capacite> > Carte::GetAbility() const
    {
        return ability;
    }
    
    void Carte::SetIsTap(bool value)
    {
        isTap = value;
    }
    
    
    void Carte::SetCounter(int value)
    {
        counters = value;
    }
    
    std::shared_ptr<Carte> Carte::Clone()
    {
        std::vector<std::shared_ptr<Capacite> > capa;
        for (unsigned int i = 0 ; i < ability.size() ; i++ )
            capa.push_back(ability[i]->Clone());
        std::shared_ptr<Cout> new_cout(new Cout());
        new_cout->SetCost(cost->GetInc(),cost->GetBlue(),cost->GetBlack(),cost->GetGreen(),0,cost->GetLife());
        std::shared_ptr<Carte> clone (new Carte(isPermanent,isLand,isCreature,isToken,this->GetName(),new_cout, capa, this->GetIdObj(), this->GetIndJoueur()));
        clone->SetCounter(counters);
        clone->SetIsTap(isTap);
        clone->SetOracle(this->GetOracle());
        //std::cout<<"\t cout de base : "<<cost->GetBlack()<<" "<<cost->GetBlue()<<" "<<cost->GetGreen()<<" "<<cost->GetInc()<<std::endl;
        //std::cout<<"\t copie du cout : "<<clone->GetCost()->GetBlack()<<" "<<clone->GetCost()->GetBlue()<<" "<<clone->GetCost()->GetGreen()<<" "<<clone->GetCost()->GetInc()<<std::endl;
        return clone;
    }
};
