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
        
        pile = new Zone (NULL,2,"pile");
        battlefield = new Zone(NULL,2,"battlefield");
        
        joueur = 0; phase = 0;
    }
    
    void Etat::IncrPhase()
    {
        phase ++;
        if (phase > NbPhase)
        {
            phase = 0;
                       
            //cleanup
            for(int i = 0; i < nbJoueur ; i++)
            {
                //vider la mana pool
                this->GetJoueur(i).GetManaPool().Vider();
                
                //retirer les blessures et effet fin tour
                for (int j = 0; j < this->GetJoueur(i).GetNbCarte() ; j++)
                    if ("battlefield" == this->GetJoueur(i).GetCarte(j).GetConteneur().GetName()
                            && false == this->GetJoueur(i).GetCarte(j).GetIsCapacite() )
                        if (((Carte)this->GetJoueur(i).GetCarte(j)).GetIsCreature())
                        {
                            ((Creature)this->GetJoueur(i).GetCarte(j)).SetBlessure(0);
                            ((Creature)this->GetJoueur(i).GetCarte(j)).SetBonusEOT(0);
                        }   
            }
            //retirer cartes en trop dans la main
            int carteTrop = 0;
            for (int i = 0 ; i < this->JoueurActif().GetNbCarte() ; i++)
                    if ("hand" == this->JoueurActif().GetCarte(i).GetConteneur().GetName())
                        carteTrop ++;
            if (carteTrop > 7)
                for(int i = 0 ; i < 7-carteTrop ; i++)
                    this->JoueurActif().Discard();
            
            // changement de tour
            joueur ++;
            if (joueur >= nbJoueur)
                joueur = 0; 
            
            //uptap & mal invoc
            for (int i = 0 ; i < this->JoueurActif().GetNbCarte() ; i++)
                if ("battlefield" == this->JoueurActif().GetCarte(i).GetConteneur().GetName())
                {
                    ((Carte)this->JoueurActif().GetCarte(i)).UnTap();
                    if (((Carte)this->JoueurActif().GetCarte(i)).GetIsCreature())
                        ((Creature)this->JoueurActif().GetCarte(i)).SetMalInvoc(false);
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
    void Etat::ToBattlefield(Objet obj)
    {
        obj.Deplacer(battlefield);
    }
    void Etat::ToPile(Objet obj)
    {
        obj.Deplacer(pile);
    }
};
