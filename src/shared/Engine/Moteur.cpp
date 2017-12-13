#include "Moteur.h"
#include <iostream>

namespace Engine
{
    Moteur::Moteur(std::shared_ptr<Etat::State> state)
    {
        currentState = state;
    }

    void Moteur::AddCommand(std::shared_ptr<Command> cmd)
    {
        commands.push_back(cmd);
    }
    
    void Moteur::Update()
    {
        if (!commands.empty())
            for (int i = 0 ; i < (int)commands.size() ; i++ )
            {
                commands[i]->Execute(currentState);
                historic.push_back(commands[i]); 
            }    
        commands.clear();
    }
    void Moteur::RollBack()
    {
        historic.back()->Undo(currentState);
        historic.pop_back();
        //std::cout<<"retour"<<std::endl;
    }
    int Moteur::HistoricSize()
    {
        return historic.size();
    }
    void Moteur::SetRecord(bool value)
    {
        record = value;
    }
    std::shared_ptr<Etat::State> Moteur::GetState()
    {
        return currentState;
    }
}
