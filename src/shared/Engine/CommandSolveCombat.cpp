#include "CommandSolveCombat.h"
#include <iostream>
namespace Engine {

    
    CommandSolveCombat::CommandSolveCombat(){}
    void CommandSolveCombat::Execute(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\texec solvecombat"<<std::endl;
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
        state->ClearAtt();
    }

    void CommandSolveCombat::Undo(std::shared_ptr<Etat::State> state) {
        //std::cout<<"\t\tundo solvecombat"<<std::endl;
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
    
    Json::Value CommandSolveCombat::Serialize() const
    {
        Json::Value val;
        val["typeCmd"] = "SolveCombat";
        Json::Value attaquant, bloqueur, bloque;
        for(unsigned int i = 0 ; i < idAttaquants.size(); i++)
            attaquant[i]["Id"] = idAttaquants[i];
        for(unsigned int i = 0 ; i < idBloqueur.size(); i++)
            bloqueur[i]["Id"] = idBloqueur[i];
        for(unsigned int i = 0 ; i < idBloque.size(); i++)
            bloque[i]["Id"] = idBloque[i];
        val["Attaquants"] = attaquant;
        val["Bloqueurs"] = bloqueur;
        val["Bloques"] = bloque;
        return val;
    }
    CommandSolveCombat* CommandSolveCombat::Deserialize(const Json::Value& in)
    {
        for (unsigned int i = 0 ; i < in["Attaquants"].size() ; i++ )
            idAttaquants.push_back(in["Attaquants"][i]["Id"].asInt());
        for (unsigned int i = 0 ; i < in["Bloqueurs"].size() ; i++ )
            idBloqueur.push_back(in["Bloqueurs"][i]["Id"].asInt());
        for (unsigned int i = 0 ; i < in["Bloques"].size() ; i++ )
            idBloque.push_back(in["Bloques"][i]["Id"].asInt());
        return this;
    }
}