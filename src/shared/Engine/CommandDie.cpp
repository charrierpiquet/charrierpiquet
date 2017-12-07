#include "CommandDie.h"
#include <iostream>

namespace Engine {

    CommandDie::CommandDie(std::shared_ptr<Etat::Carte> carte) {
        //std::cout<<"\t\tinit die"<<std::endl;
        mourant = carte;
    }

    void CommandDie::Execute(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\texec die"<<std::endl;
        bool trouver = false;
        for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
            if (state->GetBattlefield()[i]->GetIdObj() == mourant->GetIdObj() /*&& state->GetBattlefield()[i]->GetName() == name*/ && !trouver) {
                trouver = true;
                if (!mourant->GetIsToken())
                    state->GetJoueurs()[mourant->GetIndJoueur()]->AddCardGraveyard(state->GetBattlefield()[i]);
                state->DelCardBattlefield(i);
            }
    }

    void CommandDie::Undo(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\tretour die"<<std::endl;
        state->AddCardBattlefield(mourant);
        if (!mourant->GetIsToken())
            state->GetJoueurs()[mourant->GetIndJoueur()]->DelCardGraveyard(state->GetJoueurs()[mourant->GetIndJoueur()]->GetGraveyard().size() - 1);
    }
}
