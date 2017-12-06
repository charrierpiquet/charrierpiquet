#include "CommandDiscard.h"
#include <algorithm>
#include <ctime>
#include <iostream>
namespace Engine
{
    CommandDiscard::CommandDiscard(int joueur)
    {
        std::cout<<"\t\tinit discard"<<std::endl;
        iDJoueur = joueur;
    }
    void CommandDiscard::Execute(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\texec discard"<<std::endl;
        std::srand(unsigned ( std::time(0)));
        empty = state->GetJoueurs()[iDJoueur]->GetHand().empty();
        if (!empty)
        {
        int k = std::rand() % state->GetJoueurs()[iDJoueur]->GetHand().size();
        state->GetJoueurs()[iDJoueur]->AddCardGraveyard(state->GetJoueurs()[iDJoueur]->GetHand()[k]);
        state->GetJoueurs()[iDJoueur]->DelCardHand(k);
        }
    }
    void CommandDiscard::Undo(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\tundo discard"<<std::endl;
        if (!empty)
        {
            state->GetJoueurs()[iDJoueur]->AddCardHand(state->GetJoueurs()[iDJoueur]->GetGraveyard()[state->GetJoueurs()[iDJoueur]->GetGraveyard().size()-1]);
            state->GetJoueurs()[iDJoueur]->DelCardGraveyard(state->GetJoueurs()[iDJoueur]->GetGraveyard().size()-1);        
        }
    }
}