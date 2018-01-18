#include "Moteur.h"
#include <iostream>
#include <fstream>
#include <SFML/Network.hpp>
#include "Command.h"
#include "CommandActive.h"
#include "CommandAttack.h"
#include "CommandBlock.h"
#include "CommandCast.h"
#include "CommandClean.h"
#include "CommandDie.h"
#include "CommandDiscard.h"
#include "CommandDraw.h"
#include "CommandPaye.h"
#include "CommandPhase.h"
#include "CommandPriority.h"
#include "CommandResolveCard.h"
#include "CommandResolveCapa.h"
#include "CommandSolveCombat.h"
#include "CommandTour.h"
#include "CommandUntap.h"
#include "CommandVideMp.h"

namespace Engine
{
    Moteur::Moteur(std::shared_ptr<Etat::State> state, bool record , bool network ) : record (record), network(network)
    {
        currentState = state;
	historic.clear();
	commands.clear();
    }
	Moteur::Moteur() {}
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
		std::cout<<commands[i]->Serialize().toStyledString()<<std::endl;
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
		sf::Http::Request q ("command",sf::Http::Request::Method::Put,tempo.toStyledString());
		q.setField("Content-Type","application/x-www-form-urlencoded");
		http.sendRequest(q);
		std::cout<<"sortie"<<std::endl;
		std::cout<<tempo.toStyledString()<<std::endl;
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
	if (network)
	{
		sf::Http http ("http://localhost",8080);
		sf::Http::Request size ("command/-1", sf::Http::Request::Method::Get);
		auto rep = http.sendRequest(size);
		Json::Reader jsonReader;
		Json::Value jsonIn;
		if (jsonReader.parse(rep.getBody(),jsonIn))
		{
			int k = jsonIn["size"].asInt();
			sf::Http::Request q ("command/"+std::to_string(k-1),sf::Http::Request::Method::Delete);
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
	
   void Moteur::ReadCommand(Json::Value val)
   {
	std::cout<<"entree"<<std::endl;
	std::cout<<val.toStyledString()<<std::endl;
	for (unsigned int i = 0 ; i < val.size() ; i++)
	{
		std::shared_ptr<Command> cmd;
		//std::cout<<val<<std::endl;
		std::string type =  val[i]["typeCmd"].asString();
		if (type.compare("Active")==0)
			cmd = std::shared_ptr<CommandActive>((new CommandActive())->Deserialize(val[i]));
		else if (type.compare("Attack")==0)
			cmd = std::shared_ptr<CommandAttack>((new CommandAttack())->Deserialize(val[i]));
		else if (type.compare("Block")==0)
			cmd = std::shared_ptr<CommandBlock>((new CommandBlock())->Deserialize(val[i]));
		else if (type.compare("Cast")==0)
			cmd = std::shared_ptr<CommandCast>((new CommandCast())->Deserialize(val[i]));
		else if (type.compare("Clean")==0)
			cmd = std::shared_ptr<CommandClean>((new CommandClean())->Deserialize(val[i]));
		else if (type.compare("Die")==0)
			cmd = std::shared_ptr<CommandDie>((new CommandDie())->Deserialize(val[i]));
		else if (type.compare("Discard")==0)
			cmd = std::shared_ptr<CommandDiscard>((new CommandDiscard())->Deserialize(val[i]));
		else if (type.compare("Draw")==0)
			cmd = std::shared_ptr<CommandDraw>((new CommandDraw())->Deserialize(val[i]));
		else if (type.compare("Paye")==0)
			cmd = std::shared_ptr<CommandPaye>((new CommandPaye())->Deserialize(val[i]));
		else if (type.compare("Phase")==0)
			cmd = std::shared_ptr<CommandPhase>((new CommandPhase())->Deserialize(val[i]));
		else if (type.compare("Priority")==0)
			cmd = std::shared_ptr<CommandPriority>((new CommandPriority())->Deserialize(val[i]));
		else if (type.compare("ResolveCapa")==0)
			cmd = std::shared_ptr<CommandResolveCapa>((new CommandResolveCapa())->Deserialize(val[i]));
		else if (type.compare("ResolveCard")==0)
			cmd = std::shared_ptr<CommandResolveCard>((new CommandResolveCard())->Deserialize(val[i]));
		else if (type.compare("SolveCombat")==0)
			cmd = std::shared_ptr<CommandSolveCombat>((new CommandSolveCombat())->Deserialize(val[i]));
		else if (type.compare("Tour")==0)
			cmd = std::shared_ptr<CommandTour>((new CommandTour())->Deserialize(val[i]));
		else if (type.compare("Untap")==0)
			cmd = std::shared_ptr<CommandUntap>((new CommandUntap())->Deserialize(val[i]));
		else if (type.compare("VideMp")==0)
			cmd = std::shared_ptr<CommandVideMp>((new CommandVideMp())->Deserialize(val[i]));
		else
			std::cout<<"Erreur type de commande non reconnu"<<std::endl;
		
		std::cout<<cmd->Serialize().toStyledString()<<std::endl;
		historic.push_back(cmd); // ici ! ==> l'erreur viens de là (partout ça indique 165)
		cmd->Execute(currentState);
	//	this->AddCommand(cmd);
	}           
	this->Update();
     }

	Json::Value Moteur::GetCommand(int ind)	
	{
		std::cout<<ind<<" "<<historic.size()<<std::endl;
		std::shared_ptr<Command> truc = historic.at(ind); // la
		std::cout<<"ok"<<std::endl;
		Json::Value machin = truc->Serialize(); // ça craque ici
		std::cout<<machin.toStyledString()<<std::endl; // la
		return  machin;
	}

}
