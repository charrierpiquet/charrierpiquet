#include "CommandCast.h"
#include "Etat/Objet.h"
#include "Etat/State.h"
#include <iostream>

namespace Engine
{
    CommandCast::CommandCast(std::shared_ptr<Etat::Carte> carte)
    {
        std::cout<<"\t\tinit cast"<<std::endl;
        idCarte = carte->GetIdObj();
        idJoueur =  carte->GetIndJoueur();
    }
    void CommandCast::Execute(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\texec cast"<<std::endl;
        for (unsigned int i = 0 ; i < state->GetJoueurs()[idJoueur]->GetHand().size() ; i++)
            if (idCarte == state->GetJoueurs()[idJoueur]->GetHand()[i]->GetIdObj())
            {
                if (state->GetJoueurs()[idJoueur]->GetHand()[i]->GetIsLand())
                    state->GetJoueurs()[idJoueur]->SetAJoueTerrain(true);
                state->AddCardPile(state->GetJoueurs()[idJoueur]->GetHand()[i]);
                state->GetJoueurs()[idJoueur]->DelCardHand(i);
                break;
            }
    }
    void CommandCast::Undo(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\tundo cast"<<std::endl;
        if (std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size()-1]))
            state->GetJoueurs()[idJoueur]->SetAJoueTerrain(false);
        state->GetJoueurs()[idJoueur]->AddCardHand(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size()-1]));
        state->DelCardPile(state->GetPile().size()-1);
    }
}


