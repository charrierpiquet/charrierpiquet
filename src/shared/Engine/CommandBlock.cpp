#include "CommandBlock.h"
#include "Etat/Objet.h"
#include "Etat/State.h"

namespace Engine
{
    CommandBlock::CommandBlock(std::shared_ptr<Etat::Creature> bloqueur, std::shared_ptr<Etat::Creature> bloque)
    {
        idBloqueur = bloqueur->GetIdObj();
        idBloque = bloque->GetIdObj();
    }
    void CommandBlock::Execute(std::shared_ptr<Etat::State> state)
    {
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++)
        {
            if (state->GetBattlefield()[i]->GetIdObj() == idBloqueur)
                state->AddListBloqueur(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
            if (state->GetBattlefield()[i]->GetIdObj() == idBloque)
                state->AddListBloque(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
        }
    }
    void CommandBlock::Undo(std::shared_ptr<Etat::State> state)
    {
        state->DelListBloque(state->GetListBloque().size()-1);
        state->DelListBloqueur(state->GetBloqueur().size()-1);
    }
    
    
}
