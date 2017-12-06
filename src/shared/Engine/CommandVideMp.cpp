#include "CommandVideMp.h"
#include <iostream>

namespace Engine
{
    void CommandVideMp::Execute(std::shared_ptr<Etat::State> state)
    { 
        std::cout<<"\t\texec videmp"<<std::endl;
        for (unsigned int i = 0; i < state->GetJoueurs().size(); i++) {
                M.push_back(state->GetJoueurs()[i]->GetManaPool()->GetMulti());
                I.push_back(state->GetJoueurs()[i]->GetManaPool()->GetInc());
                B.push_back(state->GetJoueurs()[i]->GetManaPool()->GetBlack());
                U.push_back(state->GetJoueurs()[i]->GetManaPool()->GetBlue());
                G.push_back(state->GetJoueurs()[i]->GetManaPool()->GetGreen());
                jt.push_back(state->GetJoueurs()[i]->GetAJoueTerrain());
                
                state->GetJoueurs()[i]->GetManaPool()->SetMulti(0);
                state->GetJoueurs()[i]->GetManaPool()->SetInc(0);
                state->GetJoueurs()[i]->GetManaPool()->SetBlack(0);
                state->GetJoueurs()[i]->GetManaPool()->SetBlue(0);
                state->GetJoueurs()[i]->GetManaPool()->SetGreen(0);
               
                state->GetJoueurs()[i]->SetAJoueTerrain(false);
        }
      
    }
    void CommandVideMp::Undo(std::shared_ptr<Etat::State> state)
    {
        std::cout<<"\t\tundo videmp"<<std::endl;
        for (unsigned int i = 0; i < state->GetJoueurs().size(); i++) {
                state->GetJoueurs()[i]->GetManaPool()->SetMulti(M[i]);
                state->GetJoueurs()[i]->GetManaPool()->SetInc(I[i]);
                state->GetJoueurs()[i]->GetManaPool()->SetBlack(B[i]);
                state->GetJoueurs()[i]->GetManaPool()->SetBlue(U[i]);
                state->GetJoueurs()[i]->GetManaPool()->SetGreen(G[i]);
                state->GetJoueurs()[i]->SetAJoueTerrain(jt[i]);
        }
    }
}