#include "CommandResolveCard.h"
#include "CommandResolveCapa.h"

namespace Engine {

    CommandResolveCard::CommandResolveCard(std::shared_ptr<Etat::Carte> card, std::weak_ptr<Moteur> m) {
        engine = m;
        isPermanent = card->GetIsPermanent();
        idCarte = card->GetIdObj();
        idProp = card->GetIndJoueur();
    }

    void CommandResolveCard::Execute(std::shared_ptr<Etat::State> state) {
        if (isPermanent) {
            state->AddCardBattlefield(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1]));
            state->GetPile().pop_back();
        } else {
            for (unsigned int i = 0; i < std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1])->GetAbility().size(); i++)
                engine.lock()->AddCommand(std::shared_ptr<CommandResolveCapa>(new CommandResolveCapa(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1])->GetAbility()[i], engine)));

            state->GetJoueurs()[idProp]->AddCardGraveyard(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1]));
            state->GetPile().pop_back();
        }
    }

    void CommandResolveCard::Undo(std::shared_ptr<Etat::State> state) {
        if (isPermanent) {
            for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
                if (state->GetBattlefield()[i]->GetIdObj() == idCarte) {
                    state->AddCardPile(state->GetBattlefield()[i]);
                    state->DelCardBattlefield(i);
                }
        } else {
            state->AddCardPile(state->GetJoueurs()[idProp]->GetGraveyard()[state->GetJoueurs()[idProp]->GetGraveyard().size() - 1]);
            state->GetJoueurs()[idProp]->GetGraveyard().pop_back();
        }
    }

}