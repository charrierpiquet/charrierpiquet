#include "Carte.h"

namespace Etat
{
    Carte::Carte(bool permanent,bool land,bool creature,bool token,
            std::string nom,Cout cout, Capacite capa, int id, int prop):
    Objet(false, id, prop), cost(cout),ability(capa)
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
    
    void Carte::SetIsTap(bool value)
    {
        isTap = value;
    }
    
    int Carte::GetCounter()
    {
        return counters;
    }
    
    void Carte::SetCounter(int value)
    {
        counters = value;
    }
};