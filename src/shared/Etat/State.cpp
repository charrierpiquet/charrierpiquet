#include "State.h"
#include "Creature.h"
#include <cstddef>
#include <iostream>
#define NbPhase 15
#define MaxHand 7
namespace Etat
{
    State::State(int nb )
    {
        nbJoueur = nb ;
        
        for (int i = 0 ; i < nbJoueur ; i++)
            joueurs.push_back((std::shared_ptr<Joueur>)new Joueur());
        joueur = 0; phase = 0;
    }
    
    void State::IncrPhase()
    {
        phase ++;
        
        //vider la mana pool
        for(int i = 0; i < nbJoueur ; i++)
            joueurs[i]->GetManaPool()->Vider();
        
        if (phase > NbPhase)
        {
            phase = 0;
                       
            //cleanup   
            //retirer les blessures et effet fin tour
            for (int i=0 ; (unsigned)i < battlefield.size() ; i++)
                if (battlefield[i]->GetIsCreature())
                {
                    std::static_pointer_cast<Creature> (battlefield[i])->SetBlessure(0);
                    std::static_pointer_cast<Creature> (battlefield[i])->SetBonusEOT(0);
                }
            
            //retirer cartes en trop dans la main
            if (joueurs[priorite]->GetHand().size() > 7)
                for (int i = 0 ; (unsigned)i < joueurs[priorite]->GetHand().size() - 7 ; i++)
                    joueurs[priorite]->Discard();
            
            // changement de tour
            joueur ++;
            if (joueur >= nbJoueur)
                joueur = 0; 
            
            //uptap & mal invoc
            for (int i=0 ; (unsigned)i < battlefield.size() ; i++)
                if (battlefield[i]->GetIndJoueur() == joueur)
                {
                    battlefield[i]->SetIsTap(false);
                    if (battlefield[i]->GetIsCreature())
                        std::static_pointer_cast<Creature>(battlefield[i])->SetMalInvoc(false);
                }
            
            //draw
            joueurs[priorite]->Draw();
        }
        priorite = joueur;
    }
    
    void State::IncrPriority()
    {
        priorite ++;
        if (priorite >= nbJoueur)
            priorite = 0;
    }
    
    void State::AddCardBattlefield(Carte card)
    {
        battlefield.push_back((std::shared_ptr<Carte>)&card);
    }
    void State::AddCardPile(Objet card)
    {
        pile.push_back((std::shared_ptr<Objet>)&card);
    }
    void State::DelCardBattlefield(Carte card)
    {
        int ind =-1;
        for(int i=0 ; (unsigned)i<battlefield.size() ; i++)
            if (battlefield[i]->GetIdObj() == card.GetIdObj())
                ind = i;
        
        if (ind >= 0)
            battlefield.erase(battlefield.begin() + ind);
    }
    void State::DelCardPile(Objet card)
    {
        int ind =-1;
        for(int i=0 ; (unsigned)i<pile.size() ; i++)
            if (pile[i]->GetIdObj() == card.GetIdObj())
                ind = i;
        
        if (ind >= 0)
            pile.erase(pile.begin() + ind);
    }
    std::vector<std::shared_ptr<Joueur> > State::GetJoueurs() const
    {
        return joueurs;
    }

    int State::GetPhase() const
    {
        return phase;
    }
    
    int State::GetPriority() const
    {
        return priorite;
    }
    
    std::vector<std::shared_ptr<Objet> > State::GetPile () const
    {
        return pile;
    }
    std::vector<std::shared_ptr<Carte> > State::GetBattlefield () const
    {
        return battlefield;
    }
    
    
    std::string State::GetPhaseName() const
    {
        switch (phase)
        {
            case 0:
                return "Upkeep";
            case 1:
                return "Pre-Combat Main";
            case 2:
                return "Combat";
            case 3:
                return "Post-Combat Main";
            case 4:
                return "Clean-up";
            default :
                return "Unknow";
        }
    }
    
};
