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
		if (record) 
                	tempo.append(commands[i]->Serialize());
            }    
        commands.clear();
        
        if (!tempo.empty() && record)
            val.append(tempo);
    }
    void Moteur::RollBack()
    {
        if (record)
        {
            val[val.size()-1].removeIndex(val[val.size()-1].size()-1, &val[val.size()-1][val[val.size()-1].size()-1]);
            if (val[val.size()-1].empty())
                val.removeIndex(val.size()-1,&val[val.size()-1]);
        }
        historic.back()->Undo(currentState);
        historic.pop_back();
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
