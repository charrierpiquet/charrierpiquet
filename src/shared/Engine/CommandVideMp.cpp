#include "CommandVideMp.h"
#include <iostream>

namespace Engine
{
    CommandVideMp::CommandVideMp()
    {}
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
            Json::Value obj;
            obj["M"] = M[i];
            obj["I"] = I[i];
            obj["B"] = B[i];
            obj["U"] = U[i];
            obj["G"] = G[i];
            obj["jt"] = jt[i];
            val["Mp"+std::to_string(i)]= obj;
        }
        return val;
    }
    CommandVideMp* CommandVideMp::Deserialize (const Json::Value& in)
    {
        for (unsigned int i = 0 ; i < in.size() ; i ++)
        {
            M.push_back(in["Mp"+std::to_string(i)]["M"].asInt());
            I.push_back(in["Mp"+std::to_string(i)]["I"].asInt());
            B.push_back(in["Mp"+std::to_string(i)]["B"].asInt());
            U.push_back(in["Mp"+std::to_string(i)]["U"].asInt());
            G.push_back(in["Mp"+std::to_string(i)]["G"].asInt());
            jt.push_back(in["Mp"+std::to_string(i)]["jt"].asInt());
           
        }
        return this;
    }
}