#include "CastCommand.h"
#include "Etat/State.h"
#include "Etat/Active.h"

namespace Engine
{
    CastCommand::CastCommand(std::shared_ptr<Etat::Objet> o, std::shared_ptr<Etat::Carte> s, std::shared_ptr<Etat::Objet> t)
    {
        obj = o;
        src = s;
        target = t; // est ce que c'est vraiment utile ?
    }
    
    void CastCommand::Execute(Etat::State& state)
    {
        // actuellement on ne peux gerer que les couts simple (juste du mana)
        
        // si c'est une capacite
        if (obj->GetIsCapacite())
        {
            if (std::static_pointer_cast<Etat::Capacite>(obj)->GetCategorie() == 3) // si c'est une capacite active
                if (src != nullptr)           
                    if (!src->GetIsTap())     
                        if (state.GetJoueurs()[state.GetPriority()]->GetManaPool()->Payer(std::static_pointer_cast<Etat::Active>(obj)->GetCost()))
                        {
                            // on engage la source de la capa
                            src->SetIsTap(true);
                            // on met une capa sur la pile
                            state.AddCardPile(obj);
                        }
        }
        // si c'est une carte
        else
        {
            // si la carte est dans la main
            bool inHand = false;
            int ind = -1;
            for (int i = 0; i<(int)state.GetJoueurs()[state.GetPriority()]->GetHand().size();i++)
                if (state.GetJoueurs()[state.GetPriority()]->GetHand()[i]->GetIdObj() == obj->GetIdObj())
                {
                    inHand = true;
                    ind = i;
                }
            
            if (inHand)
                // si payer les couts.
                if (state.GetJoueurs()[state.GetPriority()]->GetManaPool()->Payer(std::static_pointer_cast<Etat::Carte>(obj)->GetCost()))
                {
                    //state.GetJoueurs()[state.GetPriority()]->GetHand().erase(state.GetJoueurs()[state.GetPriority()]->GetHand().begin() + ind);
                    state.GetJoueurs()[state.GetPriority()]->DelCardHand(ind);
                    state.AddCardPile(obj);
                }
        }
            
    }
    
}