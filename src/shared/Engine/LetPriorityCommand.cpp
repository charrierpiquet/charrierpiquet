#include "LetPriorityCommand.h"
#include "Etat/State.h"

namespace Engine
{
    void LetPriorityCommand::Execute(Etat::State& state)
    {
        // si c'est le joueur dont c'est pas le tour qui passe
        if (state.GetJoueurTour() != state.GetPriority())
        {
            // si la pile est vide
            if (state.GetPile().empty())
                // on passe a la phase suivante
                state.IncrPhase();
            // sinon
            else
            {
                // on resout l'objet au dessus de la pile
                // si c'est un permanent tu le mets sur champ de bataille
                if (!state.GetPile()[state.GetPile().size()-1]->GetIsCapacite())
                {
                    if (std::static_pointer_cast<Etat::Carte>(state.GetPile()[state.GetPile().size()-1])->GetIsPermanent())
                        state.AddCardBattlefield(state.GetPile()[state.GetPile().size()-1]);
                }
                else
                {
                    // si c'est un sort on le met dans le cimetiere de son proprietaire
                    // et on resout les capacites
                    if (!state.GetPile()[state.GetPile().size()-1]->GetIsCapacite())
                    {
                        state.GetJoueurs()[state.GetPile()[state.GetPile().size()-1]->GetIndJoueur()]->AddCardGraveyard(state.GetPile()[state.GetPile().size()-1]);
                        for (int i = 0 ; i< std::static_pointer_cast<Etat::Carte>(state.GetPile()[state.GetPile().size()-1])->GetAbility().size() ; i++)
                            Resolve( std::static_pointer_cast<Etat::Carte>(state.GetPile()[state.GetPile().size()-1])->GetAbility()[i]->GetKeyWord(), state);
                    }
                    else
                        Resolve(std::static_pointer_cast<Etat::Capacite>(state.GetPile()[state.GetPile().size()-1])->GetKeyWord(), state);                
                }
            }
        }
        // on supprime la carte du dessus de la pile
        state.DelCardPile(state.GetPile().size()-1);
        // on passe au joueur suivant
        state.IncrPriority();
  
    }
    
    void LetPriorityCommand::Resolve(std::string keyword, Etat::State &state)
    {
        switch (keyword)
        {
            case "multi":
                state.GetJoueurs()[state.GetPile()[state.GetPile().size()-1]->GetIndJoueur()]->GetManaPool()->AddMulti();
                break;
            case "blue":
                state.GetJoueurs()[state.GetPile()[state.GetPile().size()-1]->GetIndJoueur()]->GetManaPool()->AddBlue();
                break;
            case "green":
                state.GetJoueurs()[state.GetPile()[state.GetPile().size()-1]->GetIndJoueur()]->GetManaPool()->AddGreen();
                break;
            case "black":
                state.GetJoueurs()[state.GetPile()[state.GetPile().size()-1]->GetIndJoueur()]->GetManaPool()->AddBlack();
                break;
            case "inc":
                state.GetJoueurs()[state.GetPile()[state.GetPile().size()-1]->GetIndJoueur()]->GetManaPool()->AddInc();
                break;
            case "burn" :
                state.GetJoueurs()[1-state.GetPile()[state.GetPile().size()-1]->GetIndJoueur()]->SetPv( state.GetJoueurs()[1-state.GetPile()[state.GetPile().size()-1]->GetIndJoueur()]-1);
                break;
            default :
                std::cout<<"impossible de resoudre la capacite : "<<keyword<<std::endl;
                break;
        }
    }
}

