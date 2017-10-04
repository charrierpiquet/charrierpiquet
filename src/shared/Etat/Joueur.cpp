#include "Joueur.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ctime>

#define NbCarteDeck 20

namespace Etat
{
    Joueur::Joueur()
    {
        pv = 20;
        aJoueTerrain = false;
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
        hand.push_back(library.back());
        library.pop_back();
    }
    
    void Joueur::Discard()
    {
        std::srand(std::time(0));
        if (hand.size() > 0)
            hand.erase(hand.begin()+std::rand()%hand.size());
    }
    
    std::vector<Carte*> Joueur::GetHand()
    {
        return hand;
    }
    
    std::vector<Carte*> Joueur::GetLibrary()
    {
        return library;
    }
    
    std::vector<Carte*> Joueur::GetGraveyard()
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
    
    void Joueur::AddCardGraveyard(Carte card)
    {
        graveyard.push_back(&card);
    }
    void Joueur::DelCardGraveyard(Carte card)
    {
        int ind =-1;
        for(int i=0 ; (unsigned)i < graveyard.size() ; i++)
            if (graveyard[i]->GetIdObj() == card.GetIdObj())
                ind = i;
        
        if (ind >= 0)
            graveyard.erase(graveyard.begin() + ind);
    }
    
    void Joueur::AddCardLibrary(Carte card)
    {
        library.push_back(&card);
    }
    void Joueur::DelCardLibrary(Carte card)
    {
        int ind =-1;
        for(int i=0 ; (unsigned)i<library.size() ; i++)
            if (library[i]->GetIdObj() == card.GetIdObj())
                ind = i;
        
        if (ind >= 0)
            library.erase(library.begin() + ind);
    }
    
    void Joueur::AddCardHand(Carte card)
    {
        hand.push_back(&card);
    }
    void Joueur::DelCardHand(Carte card)
    {
        int ind =-1;
        for(int i=0 ; (unsigned)i<hand.size() ; i++)
            if (hand[i]->GetIdObj() == card.GetIdObj())
                ind = i;
        
        if (ind >= 0)
            hand.erase(hand.begin() + ind);
    }
};