#include "TestClient.h"
#include <vector>
#include "Ai.h"
#include "Etat.h"
#include "Render.h"
#include "Engine.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

void readCommand(Json::Value val);
void actu();

namespace Test
{
    void TestClient()
    {
        //std::vector<std::string> Decks;
        //Decks.push_back("Deck1");Decks.push_back("Deck2");
        //std::shared_ptr<Etat::State> state (new Etat::State(Decks));
        //std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(state));
        sf::Http http ("http://localhost",8080);
        sf::Http::Request req0 ("version");
        sf::Http::Response rep = http.sendRequest(req0);
        std::cout<<rep.getBody()<<std::endl;
        std::srand(std::time(NULL));
        int val = rand();
        Json::Value obj;
        obj["name"]=std::to_string(val);
        obj["free"]=true;
        //std::cout<<obj.toStyledString()<<std::endl;
        std::string str = "\'{\"name\":\""+std::to_string(val)+"\",\"free\":false}\'";
        //std::cout<<str<<std::endl;
        sf::Http::Request req1 ("user",sf::Http::Request::Method::Put,obj.toStyledString());
        //req1.setMethod(sf::Http::Request::Method::Post);
	req1.setField("Content-Type","application/x-www-form-urlencoded");
        rep = http.sendRequest(req1);
        std::cout<<rep.getBody()<<std::endl;
	
        int id = 0; // recuperer son identifiant
	Json::Reader jsonReader;
	Json::Value jsonIn;
	if (jsonReader.parse(rep.getBody(),jsonIn))
		id = jsonIn["id"].asInt();

        sf::Http::Request req2 ("user/"+std::to_string(id));
        rep = http.sendRequest(req2);
        std::cout<<rep.getBody()<<std::endl;

	// on affiche les joueurs connectes
        sf::Http::Request req3 ("user/-1");
	rep = http.sendRequest(req3);
	std::cout<<"nb joueur : "<<std::endl<<rep.getBody()<<std::endl;
	
	// tant que y a pas deux joueurs connectes
	while (1)
	{
		// attendre
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		// recuperer le nombre de joueur
		rep = http.sendRequest(req3);
		if (jsonReader.parse(rep.getBody(),jsonIn))
			if(jsonIn.size() == 2)
				break;
	}

	// init affichage et tout et tout
	std::vector<std::string> Decks;
        Decks.push_back("Deck1");Decks.push_back("Deck2");
        std::shared_ptr<Etat::State> state (new Etat::State(Decks));
        std::shared_ptr<Render::Rendu> rendu (new Render::Rendu(state,800,600,id));
        std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(state));
        
        Ai::Ia_Heuristic ia (state, moteur);
        
        sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
        window.setFramerateLimit(60);
	// on attend 1 seconde
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	// on récupère la pioche
	actu();
	// boucle de partie
	while (window.isOpen())
        {
            	sf::Event event;
            	while (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                	window.close();
		// on recupère les commandes et on les executes
		actu();
		// si c'est a nous de jouer (comparer id et priority)
		if (id == state->GetPriority())
			// on fait penser l'IA
			ia.think();
		// on attend 1 seconde
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));			
	}
	//getc(stdin);

	// on supprime le gens
        sf::Http::Request req4 ("user/"+std::to_string(id),sf::Http::Request::Method::Delete);
        rep = http.sendRequest(req4);

	// on affiche les gens connectes
      	sf::Http::Request req5 ("user/-1");
	rep = http.sendRequest(req5);
	std::cout<<"nb joueur : "<<std::endl<<rep.getBody()<<std::endl;
    }
}

void actu()
{
	sf::Http::Request request ("command/"+std::to_string(moteur->HistoricSize()));
	auto rep = http.sendRequest(request);
	Json::Reader jsonReader;
	Json::Value jsonIn;
	if (jsonReader.parse(rep.getBody(),jsonIn))
		readCommand(jsonIn);
}

void readCommand(Json::Value val)
{
	for (unsigned int i = 0 ; i < val.size() ; i++)
	{
		std::shared_ptr<Engine::Command> cmd;
		//std::cout<<val<<std::endl;
		std::string type =  val[i]["typeCmd"].asString();
		if (type.compare("Active")==0)
			cmd = std::shared_ptr<Engine::CommandActive>((new Engine::CommandActive())->Deserialize(val[i]));
		else if (type.compare("Attack")==0)
			cmd = std::shared_ptr<Engine::CommandAttack>((new Engine::CommandAttack())->Deserialize(val[i]));
		else if (type.compare("Block")==0)
			cmd = std::shared_ptr<Engine::CommandBlock>((new Engine::CommandBlock())->Deserialize(val[i]));
		else if (type.compare("Cast")==0)
			cmd = std::shared_ptr<Engine::CommandCast>((new Engine::CommandCast())->Deserialize(val[i]));
		else if (type.compare("Clean")==0)
			cmd = std::shared_ptr<Engine::CommandClean>((new Engine::CommandClean())->Deserialize(val[i]));
		else if (type.compare("Die")==0)
			cmd = std::shared_ptr<Engine::CommandDie>((new Engine::CommandDie())->Deserialize(val[i]));
		else if (type.compare("Discard")==0)
			cmd = std::shared_ptr<Engine::CommandDiscard>((new Engine::CommandDiscard())->Deserialize(val[i]));
		else if (type.compare("Draw")==0)
			cmd = std::shared_ptr<Engine::CommandDraw>((new Engine::CommandDraw())->Deserialize(val[i]));
		else if (type.compare("Paye")==0)
			cmd = std::shared_ptr<Engine::CommandPaye>((new Engine::CommandPaye())->Deserialize(val[i]));
		else if (type.compare("Phase")==0)
			cmd = std::shared_ptr<Engine::CommandPhase>((new Engine::CommandPhase())->Deserialize(val[i]));
		else if (type.compare("Priority")==0)
			cmd = std::shared_ptr<Engine::CommandPriority>((new Engine::CommandPriority())->Deserialize(val[i]));
		else if (type.compare("ResolveCapa")==0)
		{
			cmd = std::shared_ptr<Engine::CommandResolveCapa>((new Engine::CommandResolveCapa())->Deserialize(val[i]));
			std::static_pointer_cast<Engine::CommandResolveCapa>(cmd)->SetEngine(null_weak_ptr);
		}
		else if (type.compare("ResolveCard")==0)
		{
			cmd = std::shared_ptr<Engine::CommandResolveCard>((new Engine::CommandResolveCard())->Deserialize(val[i]));
			std::static_pointer_cast<Engine::CommandResolveCard>(cmd)->SetEngine(null_weak_ptr);
		}
		else if (type.compare("SolveCombat")==0)
			cmd = std::shared_ptr<Engine::CommandSolveCombat>((new Engine::CommandSolveCombat())->Deserialize(val[i]));
		else if (type.compare("Tour")==0)
			cmd = std::shared_ptr<Engine::CommandTour>((new Engine::CommandTour())->Deserialize(val[i]));
		else if (type.compare("Untap")==0)
			cmd = std::shared_ptr<Engine::CommandUntap>((new Engine::CommandUntap())->Deserialize(val[i]));
		else if (type.compare("VideMp")==0)
			cmd = std::shared_ptr<Engine::CommandVideMp>((new Engine::CommandVideMp())->Deserialize(val[i]));
		else
			std::cout<<"Erreur type de commande non reconnu"<<std::endl;
		moteur->AddCommand(cmd);
	}           
	moteur->Update();
}

