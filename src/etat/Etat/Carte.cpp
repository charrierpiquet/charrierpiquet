#include "Carte.h"

namespace Etat
{
    Carte::Carte(bool permanent,bool land,bool creature,bool token, std::string nom,
           Cout cout, Capacite capa)
    {
        isPermanent = permanent;
        isLand = land;
        isCreature = creature;
        isToken = token;
        name = nom;
        cost = cout;
        ability = capa;
        
        counters =0;
        isTap = false;
        
    }
    
    std::string Carte::GetName()
    {
        return name;
    }
    
    Cout Carte::GetCost()
    {
        return cost;
    }
    
    void Carte::SetIsTap(bool value)
    {
        isTap = value;
    }
    
    void Carte::GetCounter()
    {
        return counters;
    }
    
    void Carte::SetCounter(int value)
    {
        counters = value;
    }
    
    bool Carte::GetIsLand()
    {
        return isLand;
    }
    
    bool Carte::GetIsPermanent()
    {
        return isPermanent;
    }
    
    bool Carte::GetIsCreature()
    {
        return isCreature;
    }
    
    bool Carte::GetIsToken()
    {
        return isToken;
    }
    
    bool Carte::GetIsTap()
    {
        return isTap;
    }
};