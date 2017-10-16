#include "Creature.h"

namespace Etat
{
    Creature::Creature(int strengh, int thougness,bool token,std::string nom, Cout cout,
            std::vector<std::shared_ptr<Capacite> > capa, int id, int prop):Carte(true,false,true,token, nom, cout, capa, id, prop)
    {
        force = strengh;
        endurance = thougness;
        
        blessure = 0;
        bonusEOT = 0;
        malInvoc = true;
    }
    
    int Creature::GetForce() const
    {
        return force + GetCounter() + bonusEOT;
    }
    
    int Creature::GetEndurance() const
    {
        return endurance + GetCounter() + bonusEOT;
    }
    
    int Creature::GetBlessure() const
    {
        return blessure;
    }
    
    bool Creature::GetMalInvoc() const
    {
        return malInvoc;
    }
    
    int Creature::GetBonusEOT() const
    {
        return bonusEOT;
    }
    
    void Creature::SetBlessure(int value) 
    {
        blessure = std::max(value,0);
    }
    
    void Creature::SetBonusEOT(int value) 
    {
        bonusEOT = value;
    }
    
    void Creature::SetMalInvoc(bool value)
    {
        malInvoc = value;
    }
    

    
};