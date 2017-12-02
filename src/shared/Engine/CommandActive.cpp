#include "CommandActive.h"
#include "Etat/Objet.h"
#include "Etat/Capacite.h"
#include "Etat/State.h"

namespace Engine {

    CommandActive::CommandActive(std::shared_ptr<Etat::Carte> carte, std::shared_ptr<Etat::Capacite> capa, std::weak_ptr<Etat::Objet> target) {
        idSource = carte->GetIdObj();
        keyWord = capa->GetKeyWord();
        if (capa->GetNeedTarget())
            idTarget = target.lock()->GetIdObj();
        else
            idTarget = -1;
    }

    void CommandActive::Execute(std::shared_ptr<Etat::State> state) {
        for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
            if (state->GetBattlefield()[i]->GetIdObj() == idSource)
                if (!state->GetBattlefield()[i]->GetIsTap()) {
                    state->GetBattlefield()[i]->SetIsTap(true);
                    bool need_target = false;;
                    for (unsigned int j = 0; j < state->GetBattlefield()[i]->GetAbility().size(); j++)
                        if (state->GetBattlefield()[i]->GetAbility()[j]->GetKeyWord() == keyWord) 
                            need_target = state->GetBattlefield()[i]->GetAbility()[j]->GetNeedTarget();

                    state->AddCardPile(std::shared_ptr<Etat::Capacite>(new Etat::Capacite(nullptr, keyWord, state->GetInd(), state->GetBattlefield()[i]->GetIndJoueur(), keyWord, need_target)));
                    bool trouver = need_target;
                    if (trouver)
                        for (unsigned int j = 0; j < state->GetBattlefield().size(); j++)
                            if (state->GetBattlefield()[j]->GetIdObj() == idTarget && trouver) {
                                trouver = false;
                                state->GetPile()[state->GetPile().size() - 1]->SetTarget(std::weak_ptr<Etat::Objet>(state->GetBattlefield()[j]));
                            }

                    if (trouver)
                        for (unsigned int j = 0; j < state->GetPile().size(); j++)
                            if (state->GetPile()[j]->GetIdObj() == idTarget && trouver) {
                                trouver = false;
                                state->GetPile()[state->GetPile().size() - 1]->SetTarget(std::weak_ptr<Etat::Objet>(state->GetPile()[j]));
                            }
                }
    }

    void CommandActive::Undo(std::shared_ptr<Etat::State> state) {
        for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
            if (state->GetBattlefield()[i]->GetIdObj() == idSource) {
                state->GetBattlefield()[i]->SetIsTap(false);
                state->GetPile().pop_back();
            }
    }
}