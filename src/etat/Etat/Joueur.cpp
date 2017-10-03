#include "Joueur.h"
#include <cstddef>

#define NbCarteDeck 20

namespace Etat
{
    Joueur::Joueur()
    {
        manaPool =  new ManaPool();
        
        pv = 20;
        aJoueTerrain = false;
        
        graveyard = new Zone(this, 2, "graveyard");
        library = new Zone(this, 0,"library");
        hand = new Zone(this, 1, "hand");
        
        cartes = malloc(NbCarteDeck*sizeof(Objet));
        if (cartes == NULL)
        {
            // erreur
        }
        
        for(int i = 0; i<NbCarteDeck; i++)
            cartes[i] = new Carte();
    }
    
    int Joueur::GetPv()
    {
        return pv;
    }
    void Joueur::SetPv(int Pv)
    {
        pv = Pv;
    }
    
    void Joueur::Draw()
    {
        int i;
        bool canDraw = false;
        
        for (int j = 0 ; j < nbCarte ; j++)
            if (cartes[j].GetConteneur().GetName() == "library")
                canDraw = true;
        
        while (canDraw)
        {
            i = rand()% nbCarte;
            if (cartes[i].GetConteneur().GetName() == "library")
            {
                cartes[i].Deplacer(hand);
                break;
            }
        }  
    }
    
    void Joueur::Discard()
    {
        int i;
        bool canDiscard = false;
        
        for (int j = 0 ; j < nbCarte ; j++)
            if (cartes[j].GetConteneur().GetName() == "hand")
                canDiscard = true;
        
        while (canDiscard)
        {
            i = rand()% nbCarte;
            if (cartes[i].GetConteneur().GetName() == "hand")
            {
                cartes[i].Deplacer(graveyard);
                break;
            }
        }
    }
    
    void Joueur::Sacrifice(Objet carte)
    {
        carte.Deplacer(graveyard);
    }
    
    Zone Joueur::GetHand()
    {
        return hand;
    }
    
    Zone Joueur::GetLibrary()
    {
        return library;
    }
    
    Zone Joueur::GetGraveyard()
    {
        return graveyard;
    }
    
    ManaPool Joueur::GetManaPool()
    {
        return manaPool;
    }
    
    bool Joueur::GetAJoueTerrain()
    {
        return aJoueTerrain;
    }
    
    void Joueur::SetAJoueTerrain(bool value)
    {
        aJoueTerrain = value;
    }
    
    Objet Joueur::GetCarte(int i)
    {
        return cartes[i];
    }
    
    void Joueur::AddObjet(Objet newObj)
    {
        nbCarte ++;
        cartes = realloc(cartes,nbCarte);
        cartes[nbCarte -1] = newObj;
    }
    
    void Joueur::DestroyObjet(Objet Obj)
    {
        
    }
    
};