#include "CommandAttack.h"
#include "Etat/Objet.h"
#include "Etat/State.h"
#include <iostream>

namespace Engine
{
    CommandAttack::CommandAttack(std::shared_ptr<Etat::Creature> crea )
    {
        //std::cout<<"\t\tinit attaque"<<std::endl;
        idAttaquant = crea->GetIdObj();
    }
    void CommandAttack::Execute(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\texec attaque"<<std::endl;
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++ )
            if (state->GetBattlefield()[i]->GetIdObj() == idAttaquant)
                if ( !state->GetBattlefield()[i]->GetIsTap())
                {
                    state->GetBattlefield()[i]->SetIsTap(true);
                    state->AddListAttaquant(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
                }
    }
    void CommandAttack::Undo(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\tundo attaque"<<std::endl;
        state->GetAttaquants()[state->GetAttaquants().size()-1]->SetIsTap(false);
        state->DelListAttaquant(state->GetAttaquants().size()-1);
    }
    Json::Value CommandAttack::Serialize() const {
        Json::Value val;
        val["typeCmd"] = "Attack";
        val["idAttaquant"] = idAttaquant;
        return val;
    }

    CommandAttack* CommandAttack::Deserialize(const Json::Value& in) {
        idAttaquant = in["idAttaquant"].asInt();
        return this;
    }
}