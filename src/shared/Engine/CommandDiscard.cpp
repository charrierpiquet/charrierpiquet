#include "CommandDiscard.h"
#include <algorithm>
#include <ctime>
#include <iostream>
namespace Engine {

    CommandDiscard::CommandDiscard(int joueur) {
	std::srand(3);
        //std::cout<<"\t\tinit discard"<<std::endl;
        idJoueur = joueur;
	alea = 17;
    }

    CommandDiscard::CommandDiscard() {
    }

    void CommandDiscard::Execute(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\texec discard"<<std::endl;
        // same
        empty = state->GetJoueurs()[idJoueur]->GetHand().empty();
        if (!empty) {
            int k =  alea % state->GetJoueurs()[idJoueur]->GetHand().size();
            state->GetJoueurs()[idJoueur]->AddCardGraveyard(state->GetJoueurs()[idJoueur]->GetHand()[k]);
            state->GetJoueurs()[idJoueur]->DelCardHand(k);
        }
    }

    void CommandDiscard::Undo(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\tundo discard"<<std::endl;
        if (!empty) {
            state->GetJoueurs()[idJoueur]->AddCardHand(state->GetJoueurs()[idJoueur]->GetGraveyard()[state->GetJoueurs()[idJoueur]->GetGraveyard().size() - 1]);
            state->GetJoueurs()[idJoueur]->DelCardGraveyard(state->GetJoueurs()[idJoueur]->GetGraveyard().size() - 1);
        }
    }

    Json::Value CommandDiscard::Serialize() const {
        Json::Value val;
	val["alea"] = alea;
        val["typeCmd"] = "Discard";
        val["idJoueur"] = idJoueur;
        val["empty"] = empty;
        return val;
    }

    CommandDiscard* CommandDiscard::Deserialize(const Json::Value& in) {
        idJoueur = in["idJoueur"].asInt();
        empty = in["empty"].asBool();
	alea = in["alea"].asInt();
        return this;
    }
}
