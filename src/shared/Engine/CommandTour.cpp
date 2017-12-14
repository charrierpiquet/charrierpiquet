#include "CommandTour.h"
#include "Etat/State.h"
#include <iostream>
namespace Engine
{
    CommandTour::CommandTour(int value)
    {
        //std::cout<<"\t\tinit tour"<<std::endl;
        newTour = value;
    }
    CommandTour::CommandTour(){}
    void CommandTour::Execute(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\texec tour"<<std::endl;
        oldTour = state->GetJoueurTour();
        state->SetTour(newTour);
    }
    void CommandTour::Undo(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\tundo tour"<<std::endl;
        state->SetTour(oldTour);
    }
    
    Json::Value CommandTour::Serialize() const
    {
        Json::Value val;
        val["typeCmd"] = "Tour";
        val["old"]=oldTour;
        val["new"]=newTour;
        return val;
    }
    CommandTour* CommandTour::Deserialize(const Json::Value& in)
    {
        oldTour = in["old"].asInt();
        newTour = in["new"].asInt();
        return this;
    }
    
}