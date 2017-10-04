#include "Creature.h"

namespace Etat
{
    Creature::Creature(int strengh, int thougness,bool token,std::string nom, Cout cout,
            Capacite capa):Carte(true,false,true,token, nom, cout, capa)
    {
        force = strengh;
        endurance = thougness;
        
        blessure = 0;
        bonusEOT = 0;
        malInvoc = true;
    }
    
    int Creature::GetForce()
    {
        return force + ((Carte)this).GetCounter() + bonusEOT;
    }
    
    int Creature::GetEndurance()
    {
        return endurance + ((Carte)this).GetCounter() + bonusEOT;
    }
    
    int Creature::GetBlessure()
    {
        return blessure;
    }
    
    int Creature::GetMalInvoc()
    {
        return malInvoc;
    }
    
    int Creature::GetBonusEOT()
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