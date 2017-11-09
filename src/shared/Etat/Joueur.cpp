#include "Joueur.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>

#define NbCarteDeck 20

namespace Etat
{
    Joueur::Joueur()
    {
        pv = 20;
        aJoueTerrain = false;
        manaPool = std::shared_ptr<ManaPool>(new ManaPool());
    }
    
    int Joueur::GetPv() const
    {
        return pv;
    }
    void Joueur::SetPv(int Pv)
    {
        pv = std::max(Pv,0);
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
    
    std::vector<std::shared_ptr<Carte> > Joueur::GetHand() const
    {
        return hand;
    }
    
    std::vector<std::shared_ptr<Carte> > Joueur::GetLibrary() const
    {
        return library;
    }
    
    std::vector<std::shared_ptr<Carte> > Joueur::GetGraveyard() const
    {
        return graveyard;
    }
    
    std::shared_ptr<ManaPool> Joueur::GetManaPool() const 
    {
        return manaPool;
    }
    
    bool Joueur::GetAJoueTerrain() const
    {
        return aJoueTerrain;
    }
    
    void Joueur::SetAJoueTerrain(bool value)
    {
        aJoueTerrain = value;
    }
    
    void Joueur::AddCardGraveyard(std::shared_ptr<Carte> card)
    {
        graveyard.push_back(card);
    }
    void Joueur::DelCardGraveyard(int ind)
    {
        if (ind >= 0 && ind < (int)graveyard.size())
            graveyard.erase(graveyard.begin() + ind);
    }
    
    void Joueur::AddCardLibrary(std::shared_ptr<Carte> card)
    {
        library.push_back(card);
    }
    void Joueur::DelCardLibrary(int ind)
    {
        if (ind >= 0 && ind < (int)library.size())
            library.erase(library.begin() + ind);
    }
    
    
    void Joueur::AddCardHand(std::shared_ptr<Carte> card)
    {
        hand.push_back(card);
    }
    void Joueur::DelCardHand(int ind)
    {
        if (ind >= 0 && ind < (int)hand.size())
            hand.erase(hand.begin() + ind);
    }
};