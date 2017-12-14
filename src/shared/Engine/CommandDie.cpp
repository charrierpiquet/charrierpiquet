#include "CommandDie.h"
#include <iostream>

namespace Engine {

    CommandDie::CommandDie(std::shared_ptr<Etat::Carte> carte) {
        //std::cout<<"\t\tinit die"<<std::endl;
        id_carte = carte->GetIdObj();
        id_prop = carte->GetIndJoueur();
    }
CommandDie::CommandDie(){}
    void CommandDie::Execute(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\texec die"<<std::endl;
        bool trouver = false;
        for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
            if (state->GetBattlefield()[i]->GetIdObj() == id_carte /*&& state->GetBattlefield()[i]->GetName() == name*/ && !trouver) {
                trouver = true;
               
                    state->GetJoueurs()[state->GetBattlefield()[i]->GetIndJoueur()]->AddCardGraveyard(state->GetBattlefield()[i]);
                state->DelCardBattlefield(i);
            }
    }

    void CommandDie::Undo(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\tretour die"<<std::endl;
        state->AddCardBattlefield(state->GetJoueurs()[id_prop]->GetGraveyard()[state->GetJoueurs()[id_prop]->GetGraveyard().size() -1]);
        state->GetJoueurs()[id_prop]->DelCardGraveyard(state->GetJoueurs()[id_prop]->GetGraveyard().size() - 1);
    }
    
        Json::Value CommandDie::Serialize() const
    {
        Json::Value val;
        val["typeCmd"] = "Die";
        val["idJoueur"] = id_prop;
        val["idCarte"] = id_carte;
        return val;
    }
    CommandDie* CommandDie::Deserialize(const Json::Value& in)
    {
        id_prop = in["idJoueur"].asInt();
        id_carte = in["idCarte"].asInt();
        return this;
    }
}
