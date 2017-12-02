#include "CommandPhase.h"

namespace Engine
{
    CommandPhase::CommandPhase(int value)
    {
        newPhase = value;
    }
    void CommandPhase::Execute(std::shared_ptr<Etat::State> state)
    {
        oldPhase = state->GetPhase();
        state->SetPhase(newPhase);
    }
    void CommandPhase::Undo(std::shared_ptr<Etat::State> state)
    {
        state->SetPhase(oldPhase);
    }
}

