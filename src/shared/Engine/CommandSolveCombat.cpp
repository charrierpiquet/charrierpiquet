#include "CommandSolveCombat.h"

namespace Engine {

    void CommandSolveCombat::Execute(std::shared_ptr<Etat::State> state) {
        // recup des id
        for (unsigned int i = 0; i < state->GetAttaquants().size(); i++)
            idAttaquants.push_back(state->GetAttaquants()[i]->GetIdObj());
        for (unsigned int i = 0; i < state->GetListBloque().size(); i++)
            idBloque.push_back(state->GetListBloque()[i]->GetIdObj());
        for (unsigned int i = 0; i < state->GetBloqueur().size(); i++)
            idBloqueur.push_back(state->GetBloqueur()[i]->GetIdObj());
        // calcul des degats
        for (int i = 0; i < (int) state->GetBloqueur().size(); i++)
            state->GetListBloque()[i]->SetBlessure(state->GetListBloque()[i]->GetBlessure() + state->GetBloqueur()[i]->GetForce());

        // les creatures state->GetListBloque()s infliges leurs blessures aux creature state->GetListBloque()uses
        // dans l'ordre des creatures qui state->GetListBloque() et si ça depasse aux creatures suivantes
        for (int i = 0; i < (int) state->GetAttaquants().size(); i++) {
            bool isBlocked = false;

            for (int j = 0; j < (int) state->GetListBloque().size(); j++)
                if (state->GetAttaquants()[i] == state->GetListBloque()[j])
                    isBlocked = true;

            int dmgToDeal = state->GetAttaquants()[i]->GetForce();

            if (isBlocked) {
                for (int j = 0; j < (int) state->GetListBloque().size(); j++)
                    if (state->GetAttaquants()[i] == state->GetListBloque()[j] && dmgToDeal > 0) {
                        if (dmgToDeal >= state->GetBloqueur()[j]->GetEndurance()) {
                            dmgToDeal -= state->GetBloqueur()[j]->GetEndurance();
                            state->GetBloqueur()[j]->SetBlessure(state->GetBloqueur()[j]->GetBlessure() + state->GetBloqueur()[j]->GetEndurance());
                        } else {
                            state->GetBloqueur()[j]->SetBlessure(state->GetBloqueur()[j]->GetBlessure() + dmgToDeal);
                            dmgToDeal = 0;
                        }
                    }
            } else
                state->GetJoueurs()[1 - state->GetJoueurTour()]->SetPv(state->GetJoueurs()[1 - state->GetJoueurTour()]->GetPv() - dmgToDeal);
        }
        state->GetAttaquants().clear();
        state->GetBloqueur().clear();
        state->GetListBloque().clear();
    }

    void CommandSolveCombat::Undo(std::shared_ptr<Etat::State> state) {
        // reconstitution de la liste des attaquants
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++ )
        {
            for (unsigned int j = 0 ; j < idAttaquants.size() ; j++)
                if ( state->GetBattlefield()[i]->GetIdObj() == idAttaquants[j])
                    state->AddListAttaquant(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
             for (unsigned int j = 0 ; j < idBloqueur.size() ; j++)
                if ( state->GetBattlefield()[i]->GetIdObj() == idBloqueur[j])
                    state->AddListBloqueur(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
              for (unsigned int j = 0 ; j < idBloque.size() ; j++)
                if ( state->GetBattlefield()[i]->GetIdObj() == idBloque[j])
                    state->AddListBloque(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
        }

        // calcul des degats
        for (int i = 0; i < (int) state->GetBloqueur().size(); i++)
            state->GetListBloque()[i]->SetBlessure(state->GetListBloque()[i]->GetBlessure() - state->GetBloqueur()[i]->GetForce());

        // les creatures state->GetListBloque()s infliges leurs blessures aux creature state->GetListBloque()uses
        // dans l'ordre des creatures qui state->GetListBloque() et si ça depasse aux creatures suivantes
        for (int i = 0; i < (int) state->GetAttaquants().size(); i++) {
            bool isBlocked = false;

            for (int j = 0; j < (int) state->GetListBloque().size(); j++)
                if (state->GetAttaquants()[i] == state->GetListBloque()[j])
                    isBlocked = true;

            int dmgToDeal = state->GetAttaquants()[i]->GetForce();

            if (isBlocked) {
                for (int j = 0; j < (int) state->GetListBloque().size(); j++)
                    if (state->GetAttaquants()[i] == state->GetListBloque()[j] && dmgToDeal > 0) {
                        if (dmgToDeal >= state->GetBloqueur()[j]->GetEndurance()) {
                            dmgToDeal -= state->GetBloqueur()[j]->GetEndurance();
                            state->GetBloqueur()[j]->SetBlessure(state->GetBloqueur()[j]->GetBlessure() - state->GetBloqueur()[j]->GetEndurance());
                        } else {
                            state->GetBloqueur()[j]->SetBlessure(state->GetBloqueur()[j]->GetBlessure() - dmgToDeal);
                            dmgToDeal = 0;
                        }
                    }
            } else
                state->GetJoueurs()[1 - state->GetJoueurTour()]->SetPv(state->GetJoueurs()[1 - state->GetJoueurTour()]->GetPv() + dmgToDeal);
        }
        
    }
}