#include "Objet.h"

namespace Etat
{
    void Objet::SetTarget(Objet cible)
    {
        target = cible;
    }
    Objet Objet::GetTarget()
    {
        return target;
    }
    bool Objet::GetIsCapacite()
    {
        return isCapacite;
    }
    int Objet::GetIndJoueur()
    {
        return indJoueur;
    }
};

