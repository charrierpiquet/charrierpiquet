#include "Zone.h"

namespace Etat
{
    Zone::Zone(Joueur prop, int visi, string nom)
    {
        proprietaire = prop; // peut être null pour les zones communes
        visibilite = visi; // 0 invisible, 1 visible par le propretaire, 2 visible par tous
        name = nom;
    }
    int Zone::GetVisibilite()
    {
        return visibilite;
    }
    Joueur Zone::GetProprietaire()
    {
        return proprietaire;
    }
    string Zone::GetName()
    {
        return name;
    }
    
    
    
};