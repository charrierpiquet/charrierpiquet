#include "CommandVideMp.h"
#include <iostream>

namespace Engine
{
    void CommandVideMp::Execute(std::shared_ptr<Etat::State> state)
    { 
        //std::cout<<"\t\texec videmp"<<std::endl;
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
        //std::cout<<"\t\tundo videmp"<<std::endl;
        for (unsigned int i = 0; i < state->GetJoueurs().size(); i++) {
                state->GetJoueurs()[i]->GetManaPool()->SetMulti(M[i]);
                state->GetJoueurs()[i]->GetManaPool()->SetInc(I[i]);
                state->GetJoueurs()[i]->GetManaPool()->SetBlack(B[i]);
                state->GetJoueurs()[i]->GetManaPool()->SetBlue(U[i]);
                state->GetJoueurs()[i]->GetManaPool()->SetGreen(G[i]);
                state->GetJoueurs()[i]->SetAJoueTerrain(jt[i]);
        }
    }
    
    Json::Value CommandVideMp::Serialize() const
    {
        Json::Value val;
        val["typeCmd"] = "VideMp";
        for (unsigned int i = 0 ; i < jt.size() ; i ++)
        {
            val[i]["M"] = M[i];
            val[i]["I"] = I[i];
            val[i]["B"] = B[i];
            val[i]["U"] = U[i];
            val[i]["G"] = G[i];
            val[i]["jt"] = jt[i];
        }
        return val;
    }
    CommandVideMp* CommandVideMp::Deserialize (const Json::Value& in)
    {
        for (unsigned int i = 0 ; i < in.size() ; i ++)
        {
            M.push_back(in[i]["M"].asInt());
            I.push_back(in[i]["I"].asInt());
            B.push_back(in[i]["B"].asInt());
            U.push_back(in[i]["U"].asInt());
            G.push_back(in[i]["G"].asInt());
            jt.push_back(in[i]["jt"].asInt());
           
        }
        return this;
    }
}