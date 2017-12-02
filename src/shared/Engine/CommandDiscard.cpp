#include "CommandDiscard.h"
#include <algorithm>
#include <ctime> 

namespace Engine
{
    CommandDiscard::CommandDiscard(int joueur)
    {
        iDJoueur = joueur;
    }
    void CommandDiscard::Execute(std::shared_ptr<Etat::State> state)
    {
        std::srand(unsigned ( std::time(0)));
        int k = std::rand() % state->GetJoueurs()[iDJoueur]->GetHand().size();
        state->GetJoueurs()[iDJoueur]->AddCardGraveyard(state->GetJoueurs()[iDJoueur]->GetHand()[k]);
        state->GetJoueurs()[iDJoueur]->DelCardHand(k);
    }
    void CommandDiscard::Undo(std::shared_ptr<Etat::State> state)
    {
        state->GetJoueurs()[iDJoueur]->AddCardHand(state->GetJoueurs()[iDJoueur]->GetGraveyard()[state->GetJoueurs()[iDJoueur]->GetGraveyard().size()-1]);
        state->GetJoueurs()[iDJoueur]->GetGraveyard().pop_back();         
    }
}