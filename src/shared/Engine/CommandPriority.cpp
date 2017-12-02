#include "CommandPriority.h"

namespace Engine
{
    CommandPriority::CommandPriority(int value)
    {
        newPriority = value;
    }
    void CommandPriority::Execute(std::shared_ptr<Etat::State> state)
    {
        oldPriority = state->GetPriority();
        state->SetPriority(newPriority);
    }
    void CommandPriority::Undo(std::shared_ptr<Etat::State> state)
    {
        state->SetPriority(oldPriority);
    }
}

