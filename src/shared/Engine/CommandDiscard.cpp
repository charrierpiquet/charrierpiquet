#include "CommandDiscard.h"
#include <algorithm>
#include <ctime>
#include <iostream>
namespace Engine
{
    CommandDiscard::CommandDiscard(int joueur)
    {
        //std::cout<<"\t\tinit discard"<<std::endl;
        idJoueur = joueur;
    }
    void CommandDiscard::Execute(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\texec discard"<<std::endl;
        std::srand(unsigned ( std::time(0)));
        empty = state->GetJoueurs()[idJoueur]->GetHand().empty();
        if (!empty)
        {
        int k = std::rand() % state->GetJoueurs()[idJoueur]->GetHand().size();
        state->GetJoueurs()[idJoueur]->AddCardGraveyard(state->GetJoueurs()[idJoueur]->GetHand()[k]);
        state->GetJoueurs()[idJoueur]->DelCardHand(k);
        }
    }
    void CommandDiscard::Undo(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\tundo discard"<<std::endl;
        if (!empty)
        {
            state->GetJoueurs()[idJoueur]->AddCardHand(state->GetJoueurs()[idJoueur]->GetGraveyard()[state->GetJoueurs()[idJoueur]->GetGraveyard().size()-1]);
            state->GetJoueurs()[idJoueur]->DelCardGraveyard(state->GetJoueurs()[idJoueur]->GetGraveyard().size()-1);        
        }
    }
        
    Json::Value CommandDiscard::Serialize() const
    {
        Json::Value val;
        val["typeCmd"] = "Discard";
        val["idJoueur"] = idJoueur;
        val["empty"] = empty;
        return val;
    }
    CommandDiscard* CommandDiscard::Deserialize(const Json::Value& in)
    {
        idJoueur = in["idJoueur"].asInt();
        empty = in["empty"].asBool();
        return this;
    }
}