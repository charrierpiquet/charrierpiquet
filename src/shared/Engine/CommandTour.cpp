#include "CommandTour.h"
#include "Etat/State.h"

namespace Engine
{
    CommandTour::CommandTour(int value)
    {
        newTour = value;
    }
    void CommandTour::Execute(std::shared_ptr<Etat::State> state)
    {
        oldTour = state->GetJoueurTour();
        state->SetTour(newTour);
    }
    void CommandTour::Undo(std::shared_ptr<Etat::State> state)
    {
        state->SetTour(oldTour);
    }
    
}