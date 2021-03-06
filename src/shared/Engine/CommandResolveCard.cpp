#include "CommandResolveCard.h"
#include "CommandResolveCapa.h"
#include <iostream>
namespace Engine {

    CommandResolveCard::CommandResolveCard(std::shared_ptr<Etat::Carte> card, std::weak_ptr<Moteur> m) {
        //std::cout<<"\t\tinit resolvecard"<<std::endl;
        engine = m;
        isPermanent = card->GetIsPermanent();
        idCarte = card->GetIdObj();
        idProp = card->GetIndJoueur();
        ////std::cout<<"\t\t\tcommande : "<<isPermanent<<std::endl;
    }

    CommandResolveCard::CommandResolveCard() {
    }

    void CommandResolveCard::Execute(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\texec resolvecard"<<std::endl;
        ////std::cout<<"\t\t\tpermanent ? "<<isPermanent;
        if (isPermanent) {
            //std::cout<<"\t\t\t"<< state->GetPile()[state->GetPile().size() - 1]->GetName()<<std::endl;
		auto machin = state->GetPile();
		int ind = state->GetPile().size() -1;
		if (ind >= 0)
		{
			auto truc = machin[ind];
			if (!truc->GetIsCapacite())
		    		state->AddCardBattlefield(std::static_pointer_cast<Etat::Carte>(truc));
			else
				std::cout<<"insulte insulte insulte"<<std::endl;
		}
		else
			std::cout<<"insulte insulte insulte"<<std::endl;
            ////std::cout<<"\t champ de bataille"<<std::endl;
        } else {
            if (!engine.expired())
                for (unsigned int i = 0; i < std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1])->GetAbility().size(); i++)
                    engine.lock()->AddCommand(std::shared_ptr<CommandResolveCapa>(new CommandResolveCapa(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1])->GetAbility()[i], engine)));


            state->GetJoueurs()[idProp]->AddCardGraveyard(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1]));
            ////std::cout<<"\t cimetiere"<<std::endl;
        }
        state->DelCardPile(state->GetPile().size() - 1);
    }

    void CommandResolveCard::Undo(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\tundo resolvecard"<<std::endl;
        if (isPermanent) {
            for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
                if (state->GetBattlefield()[i]->GetIdObj() == idCarte) {
                    state->AddCardPile(state->GetBattlefield()[i]);
                    state->DelCardBattlefield(i);
                }
        } else {
            state->AddCardPile(state->GetJoueurs()[idProp]->GetGraveyard()[state->GetJoueurs()[idProp]->GetGraveyard().size() - 1]);
            state->GetJoueurs()[idProp]->DelCardGraveyard(state->GetJoueurs()[idProp]->GetGraveyard().size() - 1);
        }
    }

    Json::Value CommandResolveCard::Serialize() const {
        Json::Value val;
        val["typeCmd"] = "ResolveCard";
        val["IdCarte"] = idCarte;
        val["Permanent"] = isPermanent;
        val["Prop"] = idProp;
        return val;
    }

    CommandResolveCard* CommandResolveCard::Deserialize(const Json::Value& in) {
        idCarte = in["IdCarte"].asInt();
        isPermanent = in["Permanent"].asBool();
        idProp = in["Prop"].asBool();
        return this;
    }

    void CommandResolveCard::SetEngine(std::weak_ptr<Engine::Moteur> moteur) {
        engine = moteur;
    }

}

