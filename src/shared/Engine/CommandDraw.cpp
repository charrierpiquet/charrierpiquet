#include "CommandDraw.h"
#include <iostream>

namespace Engine
{
    CommandDraw:: CommandDraw(int joueur)
    {
        //std::cout<<"\t\tinit draw"<<std::endl;
        idJoueur = joueur;
    }
    CommandDraw:: CommandDraw(){}
    void  CommandDraw::Execute(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\texec draw"<<std::endl;
        //std::srand(unsigned ( std::time(0)));
        //int k = std::rand() % state->GetJoueurs()[idJoueur]->GetHand().size();
        empty = state->GetJoueurs()[idJoueur]->GetLibrary().empty();
        if (!empty)
        {
        state->GetJoueurs()[idJoueur]->AddCardHand(state->GetJoueurs()[idJoueur]->GetLibrary()[state->GetJoueurs()[idJoueur]->GetLibrary().size()-1]);
        state->GetJoueurs()[idJoueur]->DelCardLibrary(state->GetJoueurs()[idJoueur]->GetLibrary().size()-1);
        idCarte = state->GetJoueurs()[idJoueur]->GetHand()[state->GetJoueurs()[idJoueur]->GetHand().size()-1]->GetIdObj();
        }
    }
    void  CommandDraw::Undo(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\tundo draw"<<std::endl;
        if (! empty)
        {
        int k = -1;
        for (unsigned int i = 0 ; i < state->GetJoueurs()[idJoueur]->GetHand().size() ; i++ )
            if (state->GetJoueurs()[idJoueur]->GetHand()[i]->GetIdObj() == idCarte)
                k = i;
        state->GetJoueurs()[idJoueur]->AddCardLibrary(state->GetJoueurs()[idJoueur]->GetHand()[k]);
        state->GetJoueurs()[idJoueur]->DelCardHand(k);
        }
    }
    
    Json::Value CommandDraw::Serialize() const
    {

	std::cout<<"commandDraw"<<std::endl;

        Json::Value val;
        val["typeCmd"] = "Draw";
        val["idJoueur"] = idJoueur;
        val["idCarte"] = idCarte;
        val["empty"] = empty;
        return val;
    }
    CommandDraw* CommandDraw::Deserialize(const Json::Value& in)
    {
        idJoueur = in["idJoueur"].asInt();
        idCarte = in["idCarte"].asInt();
        empty = in["empty"].asBool();
        return this;
    }
}

