#include "Moteur.h"
#include <iostream>
#include <fstream>
#include <SFML/Network.hpp>

namespace Engine
{
    Moteur::Moteur(std::shared_ptr<Etat::State> state, bool record , bool network ) : record (record), network(network)
    {
        currentState = state;
    }
    Moteur::~Moteur()
    {
	if (record)
	{
        	std::ofstream out ("replay.txt",std::ofstream::out);
        	out << val;
        	out.close();
	}
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
		if (record || network) 
                	tempo.append(commands[i]->Serialize());
            }    
        commands.clear();

        if (!tempo.empty() && record)
            val.append(tempo);

	// envoyer commande tempo
	if (!tempo.empty() && network)
	{
		sf::Http http ("http://localhost",8080);
		sf::Http::Request q ("command",sf::Http::Request::Method::Put,tempon.toStyledString());
		q.setField("Content-Type","application/x-www-form-urlencoded");
		http.sendRequest(q);
	}
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
	// envoyer commande delete
	if (!tempo.empty() && network)
	{
		sf::Http http ("http://localhost",8080);
		sf::Http::Request size ("command/-1", sf::Http::Request::Method::Get);
		auto rep = http.sendRequest(size);
		Json::Reader jsonReader;
		Json::Value jsonIn;
		if (jsonReader.parse(rep.getBody(),jsonIn))
		{
			int k = jsonIn["size"].toInt();
			sf::Http::Request q ("command/"+std::to_string(k-1),sf::Http::Request::Method::Delete,tempon.toStyledString());
			http.sendRequest(q);
		}
	}
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
