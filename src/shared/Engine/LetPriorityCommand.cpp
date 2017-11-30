#include "LetPriorityCommand.h"
#include "Etat/State.h"
#include "Etat/Creature.h"
#include <iostream>

namespace Engine {
    
    void LetPriorityCommand::Execute(std::shared_ptr<Etat::State> state) {
        // si c'est le joueur dont c'est pas le tour qui passe
        if (state->GetJoueurTour() != state->GetPriority()) {
            // si la pile est vide
            if (state->GetPile().empty())
                // on passe a la phase suivante
                state->IncrPhase();
                // sinon
            else {
                // on resout l'objet au dessus de la pile
                if (!state->GetPile()[state->GetPile().size() - 1]->GetIsCapacite()) {
                    // si c'est un permanent tu le mets sur champ de bataille
                    if (std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1])->GetIsPermanent())
                        state->AddCardBattlefield(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1]));
                        //si c'est un sort on resout ses capa
                    else {
                        state->GetJoueurs()[state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->AddCardGraveyard(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1]));
                        for (unsigned int i = 0; i < std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1])->GetAbility().size(); i++)
                            Resolve(std::static_pointer_cast<Etat::Carte>(state->GetPile()[state->GetPile().size() - 1])->GetAbility()[i]->GetKeyWord(), state);
                    }
                } else {
                    // si c'est une capa on resout
                    Resolve(std::static_pointer_cast<Etat::Capacite>(state->GetPile()[state->GetPile().size() - 1])->GetKeyWord(), state);
                }

                // on supprime la carte du dessus de la pile
                state->DelCardPile(state->GetPile().size() - 1);
                state->IncrPriority();
            }
        } else
            state->IncrPriority();

        // on kill les creatures qui ont 0 d'endurance
        for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
            if (state->GetBattlefield()[i]->GetIsCreature())
                if (std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i])->GetEndurance() <= 0) {
                    if (!std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i])->GetIsToken())
                        state->GetJoueurs()[state->GetBattlefield()[i]->GetIndJoueur()]->AddCardGraveyard(state->GetBattlefield()[i]);
                    state->DelCardBattlefield(i);
                }

    }

    void LetPriorityCommand::Resolve(std::string keyword, std::shared_ptr<Etat::State> state) {
        std::vector<std::shared_ptr<Etat::Capacite> > capaVide;
        std::shared_ptr<Etat::Cout> coutVide (new Etat::Cout());
        //std::cout<<keyword<<" "<<keyword.compare("blue")<<" "<<keyword.compare("green")<<std::endl;
        if (keyword.compare("multi") == 0)
            state->GetJoueurs()[state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->GetManaPool()->AddMulti();
        else if (keyword.compare("blue") == 0)
            state->GetJoueurs()[state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->GetManaPool()->AddBlue();
        else if (keyword.compare("green") == 0)
            state->GetJoueurs()[state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->GetManaPool()->AddGreen();
        else if (keyword.compare("black") == 0)
            state->GetJoueurs()[state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->GetManaPool()->AddBlack();
        else if (keyword.compare("inc") == 0)
            state->GetJoueurs()[state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->GetManaPool()->AddInc();
        else if (keyword.compare("burn") == 0)
            state->GetJoueurs()[1 - state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->SetPv(state->GetJoueurs()[1 - state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->GetPv() - 1);
        else if (keyword.compare("draw") == 0)
            state->GetJoueurs()[state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->Draw();
        else if (keyword.compare("TokenRat") == 0) {
            std::shared_ptr<Etat::Creature> Rat(new Etat::Creature(1, 1, true, (std::string)"Rat", coutVide, capaVide, 0, state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()));
            Rat->SetOracle("Creature Jeton 1/1\nJeton de creature rat,\ncree par Chef des rats.");
            state->AddCardBattlefield(Rat);
        } else if (keyword.compare("TokenSquirrel") == 0) {
            std::shared_ptr<Etat::Creature> Squirrel(new Etat::Creature(1, 1, true, "Ecureuil", coutVide, capaVide, 0, state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()));
            Squirrel->SetOracle("Creature Jeton 1/1\nJeton de creature ecureuil,\ncree par Glandee.");
            state->AddCardBattlefield(Squirrel);
        } else if (keyword.compare("Folie") == 0)
            state->GetJoueurs()[1 - state->GetPile()[state->GetPile().size() - 1]->GetIndJoueur()]->Discard();
        else if (keyword.compare("Contresort") == 0) {
            std::weak_ptr<Etat::Objet> Cible(state->GetPile()[state->GetPile().size() - 1]->GetTarget());
            unsigned int i;
            for (i = 0; i < state->GetPile().size() - 1; i++)
                if (state->GetPile()[i] == Cible.lock()) {
                    if (!Cible.lock()->GetIsCapacite())
                        state->GetJoueurs()[state->GetPile()[i]->GetIndJoueur()]->AddCardGraveyard(std::static_pointer_cast<Etat::Carte>(Cible.lock()));
                    state->DelCardPile(i);
                    break;
                }
        }//state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->AddCardHand(state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary()[state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary().size()-1]);
            //state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->DelCardLibrary( state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary().size()-1);
        else
            std::cout << "impossible de resoudre la capacite : " << keyword << std::endl;


    }
}

