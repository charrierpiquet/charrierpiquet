#include "CommandPhase.h"
#include <iostream>

namespace Engine
{
    CommandPhase::CommandPhase(int value)
    {
        std::cout<<"\t\tinit phase"<<std::endl;
        newPhase = value;
    }
    void CommandPhase::Execute(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\texec phase"<<std::endl;
        oldPhase = state->GetPhase();
        state->SetPhase(newPhase);
    }
    void CommandPhase::Undo(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\tundo phase"<<std::endl;
        state->SetPhase(oldPhase);
    }
}

