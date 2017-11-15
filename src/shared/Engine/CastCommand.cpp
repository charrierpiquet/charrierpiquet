#include "CastCommand.h"
#include "Etat/State.h"
#include "Etat/Active.h"
#include <iostream>

namespace Engine
{
    CastCommand::CastCommand(std::shared_ptr<Etat::Objet> o, std::shared_ptr<Etat::Carte> s, std::shared_ptr<Etat::Objet> t)
    {
        obj = o;
        src = s;
        target = t; // est ce que c'est vraiment utile ?
    }
    
    void CastCommand::Execute(std::shared_ptr<Etat::State> state)
    {
        // actuellement on ne peux gerer que les couts simple (juste du mana)
        // si on a la priorite
        if (obj->GetIndJoueur() == state->GetPriority())
        {
            // si c'est une capacite  
            if (obj->GetIsCapacite())
            {
                if (std::static_pointer_cast<Etat::Capacite>(obj)->GetCategorie() == 1) // si c'est une capacite active
                    if (src != nullptr)  
                        if (!src->GetIsTap())  
                            if (state->GetJoueurs()[state->GetPriority()]->GetManaPool()->Payer(std::static_pointer_cast<Etat::Active>(obj)->GetCost()))
                            {
                                //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                                // on engage la source de la capa
                                src->SetIsTap(true);
                                // on met une capa sur la pile
                                state->AddCardPile(obj);
                                //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                            }
            }
            // si c'est une carte
            else
            {
                // si la carte est dans la main
                bool inHand = false;
                int ind = -1;
                for (int i = 0; i<(int)state->GetJoueurs()[state->GetPriority()]->GetHand().size();i++)
                    if (state->GetJoueurs()[state->GetPriority()]->GetHand()[i]->GetIdObj() == obj->GetIdObj())
                    {
                        inHand = true;
                        ind = i;
                    }

                if (inHand)
                {
                    bool cast = false;
                    // si c'est un permanent et que la pile est vide et que l'on est PAS dans la phase de combat
                    if (std::static_pointer_cast<Etat::Carte>(obj)->GetIsPermanent() && state->GetPhase()!=2)
                    {
                        if (state->GetPile().empty())
                        {
                            // si c'est un terrain et que l'on a pas jouer de terrain
                            if (std::static_pointer_cast<Etat::Carte>(obj)->GetIsLand() )
                            {
                                //std::cout<<"on est la"<<std::endl;
                                if(!state->GetJoueurs()[state->GetJoueurTour()]->GetAJoueTerrain() && state->GetJoueurTour() == state->GetPriority())
                                {
                                    //std::cout<<"on lance le terrain"<<std::endl;
                                    cast = true;
                                    state->GetJoueurs()[state->GetJoueurTour()]->SetAJoueTerrain(true);
                                }
                            }
                            else
                                cast = true;
                        }
                    }
                    else
                        cast = true;

                    if (cast)
                    {
                        // si payer les couts.
                        if (state->GetJoueurs()[state->GetPriority()]->GetManaPool()->Payer(std::static_pointer_cast<Etat::Carte>(obj)->GetCost()))
                        {
                            //state->GetJoueurs()[state->GetPriority()]->GetHand().erase(state->GetJoueurs()[state->GetPriority()]->GetHand().begin() + ind);
                            state->GetJoueurs()[state->GetPriority()]->DelCardHand(ind);
                            state->AddCardPile(obj);
                        }
                    }
                }
            }
        }
            
    }
    
}