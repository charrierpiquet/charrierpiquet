#include "Moteur.h"
#include <iostream>
#include <fstream>
namespace Engine
{
    Moteur::Moteur(std::shared_ptr<Etat::State> state)
    {
        currentState = state;
    }
    Moteur::~Moteur()
    {
        std::ofstream out ("replay.txt",std::ofstream::out);
        out << val;
        out.close();
    }

    void Moteur::AddCommand(std::shared_ptr<Command> cmd)
    {
        commands.push_back(cmd);
    }
    
    void Moteur::Update()
    {
        Json::Value tempo;
        if (!commands.empty())
            for (int i = 0 ; i < (int)commands.size() ; i++ )
            {
                commands[i]->Execute(currentState);
                historic.push_back(commands[i]); 
                tempo.append(commands[i]->Serialize());
            }    
        commands.clear();
        
        if (!tempo.empty())
            val.append(tempo);
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
