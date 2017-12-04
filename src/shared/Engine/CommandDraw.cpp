#include "CommandDraw.h"

namespace Engine
{
     CommandDraw:: CommandDraw(int joueur)
    {
        idJoueur = joueur;
    }
    void  CommandDraw::Execute(std::shared_ptr<Etat::State> state)
    {
        //std::srand(unsigned ( std::time(0)));
        //int k = std::rand() % state->GetJoueurs()[idJoueur]->GetHand().size();
        state->GetJoueurs()[idJoueur]->AddCardHand(state->GetJoueurs()[idJoueur]->GetLibrary()[state->GetJoueurs()[idJoueur]->GetLibrary().size()-1]);
        state->GetJoueurs()[idJoueur]->GetLibrary().pop_back();
        idCarte = state->GetJoueurs()[idJoueur]->GetHand()[state->GetJoueurs()[idJoueur]->GetHand().size()-1]->GetIdObj();
    }
    void  CommandDraw::Undo(std::shared_ptr<Etat::State> state)
    {
        int k = -1;
        for (unsigned int i = 0 ; i < state->GetJoueurs()[idJoueur]->GetHand().size() ; i++ )
            if (state->GetJoueurs()[idJoueur]->GetHand()[i]->GetIdObj() == idCarte)
                k = i;
        state->GetJoueurs()[idJoueur]->AddCardLibrary(state->GetJoueurs()[idJoueur]->GetHand()[k]);
        state->GetJoueurs()[idJoueur]->DelCardHand(k);
    }
}