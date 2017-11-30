#include "CastCommand.h"
#include "Etat/State.h"
#include "Etat/Active.h"
#include <iostream>

namespace Engine {

    CastCommand::CastCommand(std::shared_ptr<Etat::Objet> o, std::shared_ptr<Etat::Carte> s, std::shared_ptr<Etat::Objet> t) {
        obj = o;
        src = s;
        target = t; // est ce que c'est vraiment utile ?

        obj->SetTarget(std::weak_ptr<Etat::Objet>(target));
    }

    void CastCommand::Execute(std::shared_ptr<Etat::State> state) {
        if (state != nullptr) {
            //std::cout << "\t\ton veux lancer " << obj->GetName() << std::endl;
            // actuellement on ne peux gerer que les couts simple (juste du mana)
            // si on a la priorite
            if (obj->GetIndJoueur() == state->GetPriority()) {
                //std::cout << "\t\ton a la priorite" << std::endl;
                // si c'est une capacite  
                if (obj->GetIsCapacite()) {
                    //std::cout << "\t\tc'est une capacite" << std::endl;
                        if (src != nullptr) {
                            //std::cout << "\t\tsa source est " << src->GetName() << std::endl;
                            if (!src->GetIsTap()) {
                                //std::cout << "\t\tsa source est degage" << std::endl;
                                bool test = true;
                                auto cost = std::static_pointer_cast<Etat::Active>(obj)->GetCost();
                                auto pool = state->GetJoueurs()[state->GetPriority()]->GetManaPool();
                                if (cost != nullptr) {
                                    test = pool->Payer(cost);
                                }

                                if (test) {
                                    //std::cout << "\t\ton peux payer son cout" << std::endl;
                                    if (state->GetJoueurs()[state->GetPriority()]->GetPv() > std::static_pointer_cast<Etat::Active>(obj)->GetCost()->GetLife()) {
                                        state->GetJoueurs()[state->GetPriority()]->SetPv(state->GetJoueurs()[state->GetPriority()]->GetPv() - std::static_pointer_cast<Etat::Active>(obj)->GetCost()->GetLife());
                                        ////std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                                        // on engage la source de la capa
                                        src->SetIsTap(true);
                                        // on met une capa sur la pile
                                        state->AddCardPile(obj);
                                        ////std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                                        //std::cout << "\t\ton paye les couts et on met " << obj->GetName() << " sur la pile" << std::endl;
                                    }
                                }
                            }
                    }
                }// si c'est une carte
                else {
                    //std::cout << "\t\t" << obj->GetName() << " est une carte" << std::endl;
                    // si la carte est dans la main
                    bool inHand = false;
                    int ind = -1;
                    for (int i = 0; i < (int) state->GetJoueurs()[state->GetPriority()]->GetHand().size(); i++)
                        if (state->GetJoueurs()[state->GetPriority()]->GetHand()[i]->GetIdObj() == obj->GetIdObj()) {
                            inHand = true;
                            ind = i;
                        }

                    if (inHand) {
                        //std::cout << "\t\t" << obj->GetName() << " est en main" << std::endl;
                        bool cast = false;
                        // si c'est un permanent et que la pile est vide et que l'on est PAS dans la phase de combat
                        if (std::static_pointer_cast<Etat::Carte>(obj)->GetIsPermanent() && (state->GetPhase() == 0 || state->GetPhase() == 4)) {
                            //std::cout << "\t\t" << obj->GetName() << " est un permanent et la phase permet de le lancer" << std::endl;
                            if (state->GetPile().empty()) {
                                //std::cout << "\t\tla pile est vide on peux lancer " << obj->GetName() << std::endl;
                                // si c'est un terrain et que l'on a pas jouer de terrain
                                if (std::static_pointer_cast<Etat::Carte>(obj)->GetIsLand()) {
                                    //std::cout << "\t\ten fait c'est un terrain" << std::endl;
                                    ////std::cout<<"on est la"<<std::endl;
                                    if (!state->GetJoueurs()[state->GetJoueurTour()]->GetAJoueTerrain() && state->GetJoueurTour() == state->GetPriority()) {
                                        ////std::cout<<"on lance le terrain"<<std::endl;
                                        cast = true;
                                        state->GetJoueurs()[state->GetJoueurTour()]->SetAJoueTerrain(true);
                                    }
                                } else
                                    cast = true;
                            }
                        } else
                            cast = true;

                        if (cast) {
                            //std::cout << "\t\ton peux lancer " << obj->GetName() << std::endl;
                            // si payer les couts.
                            if (state->GetJoueurs()[state->GetPriority()]->GetManaPool()->Payer(std::static_pointer_cast<Etat::Carte>(obj)->GetCost())) {
                                //std::cout << "\t\ton a paye les couts de " << obj->GetName() << std::endl;
                                //state->GetJoueurs()[state->GetPriority()]->GetHand().erase(state->GetJoueurs()[state->GetPriority()]->GetHand().begin() + ind);
                                state->GetJoueurs()[state->GetPriority()]->DelCardHand(ind);
                                state->AddCardPile(obj);
                                //std::cout << "\t\ton met " << obj->GetName() << " sur la pile" << std::endl;
                            }
                        }
                    }
                }
            }
            //std::cout << "\t\tfin lancement " << obj->GetName() << std::endl;
        }
            //std::cout << "\t\t heu... WTF ?!" << std::endl;
    }

    std::shared_ptr<Etat::Objet> CastCommand::GetObj() {
        return obj;
    }

    std::shared_ptr<Etat::Carte> CastCommand::GetSrc() {
        return src;
    }

    std::shared_ptr<Etat::Objet> CastCommand::GetTarget() {
        return target;
    }
}