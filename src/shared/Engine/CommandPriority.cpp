#include "CommandPriority.h"
#include <iostream>
namespace Engine
{
    CommandPriority::CommandPriority(int value)
    {
        std::cout<<"\t\tinit priority"<<std::endl;
        newPriority = value;
    }
    void CommandPriority::Execute(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\texec priority"<<std::endl;
        oldPriority = state->GetPriority();
        state->SetPriority(newPriority);
    }
    void CommandPriority::Undo(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\tundo priority"<<std::endl;
        state->SetPriority(oldPriority);
    }
}

