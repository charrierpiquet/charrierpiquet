#include "CommandDie.h"

namespace Engine {

    CommandDie::CommandDie(std::shared_ptr<Etat::Carte> carte) {
        idCarte = carte->GetIdObj();
        //isToken = carte->GetIsToken();
        //name = carte->GetName();
        idProp = carte->GetIndJoueur();
    }

    void CommandDie::Execute(std::shared_ptr<Etat::State> state) {
        bool trouver = false;
        for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
            if (state->GetBattlefield()[i]->GetIdObj() == idCarte /*&& state->GetBattlefield()[i]->GetName() == name*/ && !trouver) {
                trouver = true;
                state->GetJoueurs()[idProp]->AddCardGraveyard(state->GetBattlefield()[i]);
                state->DelCardBattlefield(i);
            }
    }

    void CommandDie::Undo(std::shared_ptr<Etat::State> state) {
        state->AddCardBattlefield(state->GetJoueurs()[idProp]->GetGraveyard()[state->GetJoueurs()[idProp]->GetGraveyard().size() - 1]);
        state->GetJoueurs()[idProp]->GetGraveyard().pop_back();
    }
}
