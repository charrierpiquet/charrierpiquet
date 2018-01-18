#include "Creature.h"
#include <iostream>

namespace Etat
{
    Creature::Creature(int strengh, int thougness,bool token,std::string nom, std::shared_ptr<Cout> cout,
            std::vector<std::shared_ptr<Capacite> > capa, int id, int prop):Carte(true,false,true,token, nom, cout, capa, id, prop)
    {
        force = strengh;
        endurance = thougness;
        
        //bonusEOT = std::shared_ptr<int>(new int(0));
        //blessure = std::shared_ptr<int>(new int(0));
        
        bonusEOT = 0; blessure = 0;
       
        malInvoc = true;
    }
    
    int Creature::GetForce()
    {
        return force + GetCounter() + bonusEOT;
    }
    
    int Creature::GetEndurance()
    {
        return endurance + GetCounter() + bonusEOT - blessure;
    }
    
    int Creature::GetBlessure()
    {
        //std::cout<<blessure<<std::endl;
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
