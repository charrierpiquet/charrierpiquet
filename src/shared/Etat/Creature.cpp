#include "Creature.h"

namespace Etat
{
    Creature::Creature(int strengh, int thougness,bool token,std::string nom, Cout cout,
            std::vector<Capacite> capa, int id, int prop):Carte(true,false,true,token, nom, cout, capa, id, prop)
    {
        force = strengh;
        endurance = thougness;
        
        blessure = 0;
        bonusEOT = 0;
        malInvoc = true;
    }
    
    int Creature::GetForce()
    {
        return force + GetCounter() + bonusEOT;
    }
    
    int Creature::GetEndurance()
    {
        return endurance + GetCounter() + bonusEOT;
    }
    
    int Creature::GetBlessure()
    {
        return blessure;
    }
    
    bool Creature::GetMalInvoc()
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