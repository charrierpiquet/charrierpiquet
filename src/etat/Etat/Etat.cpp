#include "Etat.h"
#include "Carte.h"
#include "Creature.h"
#include <cstddef>
#define NbPhase 15
#define MaxHand 7
namespace Etat
{
    Etat::Etat(int nb)
    {
        nbJoueur = nb ;
        joueurs = malloc(sizeof(Joueur)*nbJoueur);
        
        if (joueurs == NULL)
        {
           // erreur
        }
        
        for(int i = 0; i < nbJoueur; i++)
        {
            joueurs[i] = new Joueur( );
        }
        
        pile = new std::vector<Objet> ();
        battlefield = new std::vector<Objet> ();
        
        joueur = 0; phase = 0;
    }
    
    void Etat::IncrPhase()
    {
        phase ++;
        
        // gestion des morts
        for (int i=0 ; i < battlefield.size() ; i++)
            if (((Carte)battlefield[i]).GetIsCreature())
                if (((Creature)battlefield[i]).GetBlessure() >= ((Creature)battlefield[i]).GetEndurance())
                {
                    joueurs[battlefield[i].GetIndJoueur()].AddCardGraveyard(battlefield[i]);
                    this->DelCardBattlefield(battlefield[i]);
                }
        
        //vider la mana pool
        for(int i = 0; i < nbJoueur ; i++)
            this->GetJoueur(i).GetManaPool().Vider();
        
        if (phase > NbPhase)
        {
            phase = 0;
                       
            //cleanup

                
            //retirer les blessures et effet fin tour
            for (int i=0 ; i < battlefield.size() ; i++)
                if (((Carte)battlefield[i]).GetIsCreature())
                {
                    ((Creature)battlefield[i]).SetBlessure(0);
                    ((Creature)battlefield[i]).SetBonusEOT(0);
                }
            
            //retirer cartes en trop dans la main
            if (this->JoueurActif().GetHand().size() > 7)
                for (int i = 0 ; i < this->JoueurActif().GetHand().size() - 7 ; i++)
                    this->JoueurActif().Discard();
            
            // changement de tour
            joueur ++;
            if (joueur >= nbJoueur)
                joueur = 0; 
            
            //uptap & mal invoc
            for (int i=0 ; i < battlefield.size() ; i++)
                if (battlefield[i].GetIndJoueur() == joueur)
                {
                    ((Carte)battlefield[i]).UnTap();
                    if (((Carte)battlefield[i]).GetIsCreature())
                        ((Creature)battlefield[i]).SetMalInvoc(false);
                }
            
            //draw
            this->JoueurActif().Draw();
        }
        priorite = joueur;
    }
    
    void Etat::IncrPriority()
    {
        priorite ++;
        if (priorite >= nbJoueur)
            priorite = 0;
    }
    
    void Etat::JoueurActif()
    {
        return joueurs[priorite];
    }
    void Etat::AddCardBattlefield(Objet card)
    {
        battlefield.push_back(card);
    }
    void Etat::AddCardPile(Objet card)
    {
        pile.push_back(card);
    }
    void Etat::DelCardBattlefield(Objet card)
    {
        int ind =-1;
        for(int i=0 ; i<battlefield.size() ; i++)
            if (battlefield[i] == card)
                ind = i;
        
        if (ind >= 0)
            battlefield.erase(battlefield.begin + ind);
    }
    void Etat::DelCardPile(Objet card)
    {
        int ind =-1;
        for(int i=0 ; i<pile.size() ; i++)
            if (pile[i] == card)
                ind = i;
        
        if (ind >= 0)
            pile.erase(pile.begin + ind);
    }
};
