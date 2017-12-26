#include "CommandPriority.h"
#include <iostream>
namespace Engine
{
    CommandPriority::CommandPriority(int value)
    {
        //std::cout<<"\t\tinit priority"<<std::endl;
        newPriority = value;
    }
    CommandPriority::CommandPriority(){}
    void CommandPriority::Execute(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\texec priority"<<std::endl;
        oldPriority = state->GetPriority();
        state->SetPriority(newPriority);
    }
    void CommandPriority::Undo(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\tundo priority"<<std::endl;
        state->SetPriority(oldPriority);
    }
    
    Json::Value CommandPriority::Serialize() const
    {
        Json::Value val;
        val["typeCmd"] = "Priority";
        val["old"]=oldPriority;
        val["new"]=newPriority;
        return val;
    }
    CommandPriority* CommandPriority::Deserialize(const Json::Value& in)
    {
        oldPriority = in["old"].asInt();
        newPriority = in["new"].asInt();
        return this;
    }
}

