#include "Objet.h"

namespace Etat
{
    Objet::Objet(bool capa, int id, int prop)
    {
        isCapacite = capa;
        idObj = id;
        indJoueur = prop;
    }
    
    void Objet::SetTarget(Objet cible)
    {
        target = &cible;
    }
    Objet Objet::GetTarget()
    {
        return *target;
    }
    bool Objet::GetIsCapacite()
    {
        return isCapacite;
    }
    int Objet::GetIndJoueur()
    {
        return indJoueur;
    }
    int Objet::GetIdObj()
    {
        return idObj;
    }
    
};

