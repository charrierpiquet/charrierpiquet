#include "CommandAttack.h"
#include "Etat/Objet.h"
#include "Etat/State.h"

namespace Engine
{
    CommandAttack::CommandAttack(std::shared_ptr<Etat::Creature> crea )
    {
        idAttaquant = crea->GetIdObj();
    }
    void CommandAttack::Execute(std::shared_ptr<Etat::State> state)
    {
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++ )
            if (state->GetBattlefield()[i]->GetIdObj() == idAttaquant)
                if ( !state->GetBattlefield()[i]->GetIsTap())
                {
                    state->GetBattlefield()[i]->SetIsTap(true);
                    state->AddListAttaquant(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
                }
    }
    void CommandAttack::Undo(std::shared_ptr<Etat::State> state)
    {
        state->GetAttaquants()[state->GetAttaquants().size()-1]->SetIsTap(false);
        state->GetAttaquants().pop_back();
    }
}