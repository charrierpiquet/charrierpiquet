#include "Carte.h"

namespace Etat
{
    Carte::Carte(bool permanent,bool land,bool creature,bool token,
            std::string nom,Cout cout, std::vector<std::shared_ptr<Capacite> > capa, int id, int prop):
    Objet(false, id, prop, nom), cost(cout),ability(capa)
    {
        isPermanent = permanent;
        isLand = land;
        isCreature = creature;
        isToken = token;
        name = nom;        
        
        counters =0;
        isTap = false;
        
    }
    
    Cout Carte::GetCost() const
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
};