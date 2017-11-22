#include "State.h"
#include "Creature.h"
#include <cstddef>
#include <iostream>
#define NbPhase 4
#define MaxHand 7
namespace Etat
{
    State::State(int nb )
    {
        nbJoueur = nb ;
        
        for (int i = 0 ; i < nbJoueur ; i++)
            joueurs.push_back(std::shared_ptr<Joueur>(new Joueur()));
        joueur = 0; phase = 0; priorite =0;
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
            list_attaquant.clear();
            //cleanup   
            //retirer les blessures et effet fin tour
            for (unsigned int i=0 ; i < battlefield.size() ; i++)
                if (battlefield[i]->GetIsCreature())
                {
                    std::static_pointer_cast<Creature> (battlefield[i])->SetBlessure(0);
                    std::static_pointer_cast<Creature> (battlefield[i])->SetBonusEOT(0);
                }
            
            //retirer cartes en trop dans la main
            if (joueurs[priorite]->GetHand().size() > 7)
                for (unsigned int i = 0 ; i < joueurs[priorite]->GetHand().size() - 7 ; i++)
                    joueurs[priorite]->Discard();
            
            // changement de tour
            joueur ++;
            if (joueur >= nbJoueur)
                joueur = 0; 
            
            //uptap & mal invoc
            for (unsigned int i=0 ; i < battlefield.size() ; i++)
                if (battlefield[i]->GetIndJoueur() == joueur)
                {
                    battlefield[i]->SetIsTap(false);
                    if (battlefield[i]->GetIsCreature())
                        std::static_pointer_cast<Creature>(battlefield[i])->SetMalInvoc(false);
                }
            
            //draw
            joueurs[priorite]->Draw();
            // il a le droit de rejouer un terrain
            joueurs[priorite]->SetAJoueTerrain(false);
        }
        priorite = joueur;
    }
    
    void State::IncrPriority()
    {
        priorite = (priorite +1) %2;
    }
    
    void State::AddCardBattlefield(std::shared_ptr<Carte> card)
    {
        battlefield.push_back(card);
    }
    void State::AddCardPile(std::shared_ptr<Objet> card)
    {
        pile.push_back(card);
    }
    void State::DelCardBattlefield(int ind)
    {
        if (ind >= 0 && ind < (int)battlefield.size())
            battlefield.erase(battlefield.begin() + ind);
    }
    void State::DelCardPile(int ind)
    {
        if (ind >= 0 && ind < (int)pile.size())
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
                return "Pre-Combat Main";
            case 1:
                return "Declaration Attaquant";
            case 2:
                return "Priorite combat";
            case 3:
                return "Declaration Bloqueurs";
            case 4:
                return "Post-Combat Main";
            default :
                return "Unknow";
        }
    }
    
    int State::GetJoueurTour() const
    {
        return joueur;
    }
    
    void State::AddListAttaquant(std::shared_ptr<Creature> crea)
    {
        list_attaquant.push_back(crea);
    }
    
    std::vector<std::shared_ptr<Creature> > State::GetAttaquants() const
    {
        return list_attaquant;
    }
    
    std::shared_ptr<State> State::Clone()
    {
        std::shared_ptr<State> clone = std::shared_ptr<State>(new State(nbJoueur));
        // mettre les phases au bon stade
        while (clone->GetPhase() != this->GetPhase() && clone->GetJoueurTour() != this->GetJoueurTour() && clone->GetPriority() != this->GetPriority())
            clone->IncrPriority();
         
        // copier le champ de batailles et la pile et les liste d'attaquant
        // voir si on a pas besoin de faire des tests (si jamais ça utilise carte.clone pour une crea)
        for ( int i = 0 ; i < this->GetBattlefield().size() ; i++ )
            clone->AddCardBattlefield(this->GetBattlefield()[i]->Clone());
        for ( int i = 0 ; i < this->GetPile().size() ; i++ )
            clone->AddCardPile(this->GetPile()[i]->Clone());
        for ( int i = 0 ; i < this->GetAttaquants().size() ; i++ )
            clone->AddListAttaquant(this->GetAttaquants()[i]->Clone());
        
        // copier les joueurs
        for ( int i = 0 ; i < this->GetJoueurs().size() ; i++ )
        {
            clone->GetJoueurs()[i]->SetAJoueTerrain( this->GetJoueurs()[i]->GetAJoueTerrain());
            clone->GetJoueurs()[i]->SetPv( this->GetJoueurs()[i]->GetPv());
            // les 3 zones
            for ( int j = 0 ; j < this->GetJoueurs()[i]->GetGraveyard().size() ; j++ )
                clone->GetJoueurs()[i]->AddCardGraveyard(this->GetJoueurs()[i]->GetGraveyard()[j]->Clone());
            for ( int j = 0 ; j < this->GetJoueurs()[i]->GetLibrary().size() ; j++ )
                clone->GetJoueurs()[i]->AddCardLibrary(this->GetJoueurs()[i]->GetLibrary()[j]->Clone());
            for ( int j = 0 ; j < this->GetJoueurs()[i]->GetHand().size() ; j++ )
                clone->GetJoueurs()[i]->AddCardHand(this->GetJoueurs()[i]->GetHand()[j]->Clone());
            // la manapool
            for ( int j = 0 ; j < this->GetJoueurs()[i]->GetManaPool()->GetBlack() ; j++ )
                clone->GetJoueurs()[i]->GetManaPool()->AddBlack();
            for ( int j = 0 ; j < this->GetJoueurs()[i]->GetManaPool()->GetBlue() ; j++ )
                clone->GetJoueurs()[i]->GetManaPool()->AddBlue();
            for ( int j = 0 ; j < this->GetJoueurs()[i]->GetManaPool()->GetGreen() ; j++ )
                clone->GetJoueurs()[i]->GetManaPool()->AddGreen();
            for ( int j = 0 ; j < this->GetJoueurs()[i]->GetManaPool()->GetMulti() ; j++ )
                clone->GetJoueurs()[i]->GetManaPool()->AddMulti();
            for ( int j = 0 ; j < this->GetJoueurs()[i]->GetManaPool()->GetInc() ; j++ )
                clone->GetJoueurs()[i]->GetManaPool()->AddInc();
        }
        // gerer les cibles
        for ( int i = 0 ; i < this->GetPile().size() ; i++ )
            if (this->GetPile()[i]->GetTarget().lock().get() != nullptr)
            {
                bool trouve = false;
                for ( int j = 0 ; j < this->GetPile().size() ; j++ )
                    if (this->GetPile()[j] == this->GetPile()[i]->GetTarget().lock() && !trouve )
                    {
                        trouve = true;
                        clone->GetPile()[i]->SetTarget(std::weak_ptr<Objet>(this->GetPile()[j]));
                    }
                if (!trouve)
                    for ( int j = 0 ; j < this->GetBattlefield().size() ; j++ )
                        if (this->GetBattlefield()[j] == this->GetPile()[i]->GetTarget().lock() && !trouve )
                        {
                            trouve = true;
                            clone->GetPile()[i]->SetTarget(std::weak_ptr<Objet>(this->GetBattlefield()[j]));
                        }
            }
        
        return clone;
    }
    
};
