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
        
        graveyard = new std::vector<Objet>();
        library =  new std::vector<Objet>();
        hand =  new std::vector<Objet>();
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
        if (hand.size() > 0)
            hand.erase(hand.begin()+rand()%hand.size());
    }
    
    std::vector<Objet> Joueur::GetHand()
    {
        return hand;
    }
    
    std::vector<Objet> Joueur::GetLibrary()
    {
        return library;
    }
    
    std::vector<Objet> Joueur::GetGraveyard()
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
    
    void Joueur::AddCardGraveyard(Objet card)
    {
        graveyard.push_back(card);
    }
    void Joueur::DelCardGraveyard(Objet card)
    {
        int ind =-1;
        for(int i=0 ; i<graveyard.size() ; i++)
            if (graveyard[i] == card)
                ind = i;
        
        if (ind >= 0)
            graveyard.erase(graveyard.begin + ind);
    }
    
    void Joueur::AddCardLibrary(Objet card)
    {
        library.push_back(card);
    }
    void Joueur::DelCardLibrary(Objet card)
    {
        int ind =-1;
        for(int i=0 ; i<library.size() ; i++)
            if (library[i] == card)
                ind = i;
        
        if (ind >= 0)
            library.erase(library.begin + ind);
    }
    
    void Joueur::AddCardHand(Objet card)
    {
        hand.push_back(card);
    }
    void Joueur::DelCardHand(Objet card)
    {
        int ind =-1;
        for(int i=0 ; i<hand.size() ; i++)
            if (hand[i] == card)
                ind = i;
        
        if (ind >= 0)
            hand.erase(hand.begin + ind);
    }
};