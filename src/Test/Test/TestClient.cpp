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

void actu(std::shared_ptr<Engine::Moteur>);

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
        std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(state,false, true));
        
        Ai::Ia_Heuristic ia (state, moteur);
        
        sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
        window.setFramerateLimit(60);
	// on attend 1 seconde
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	// on récupère la pioche
	actu(moteur);
	// boucle de partie
	while (window.isOpen())
        {
            	sf::Event event;
            	while (window.pollEvent(event))

		{
                if (event.type == sf::Event::Closed)
                	window.close();
                if (event.type == sf::Event::MouseButtonPressed)
                    if (event.mouseButton.button == sf::Mouse::Left)
                        rendu->Click(event.mouseButton.x,event.mouseButton.y);
		}
		// on recupère les commandes et on les executes
		actu(moteur);
		// si c'est a nous de jouer (comparer id et priority)
		if (id == state->GetPriority())
			// on fait penser l'IA
			ia.Think();
		// on attend 1 seconde
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));	

		window.clear(sf::Color::Black);
            	rendu->Draw(window);
            	//std::cout<<(int)(Foret1->GetIsTap())<<std::endl;
            	window.display();		
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

void actu(std::shared_ptr<Engine::Moteur> moteur)
{
	sf::Http http ("http://localhost",8080); // oui c'est moche
	sf::Http::Request req ("command/-1");
	Json::Reader jsonReader;
	Json::Value jsonIn;
	int k=-1;
	auto nb = http.sendRequest(req);
	if (jsonReader.parse(nb.getBody(),jsonIn))
		k = jsonIn["Size"].asInt();
	
	if (k != moteur->HistoricSize())
	{
		sf::Http::Request request ("command/"+std::to_string(moteur->HistoricSize()));
		auto rep = http.sendRequest(request);
		jsonIn.clear();
		if (jsonReader.parse(rep.getBody(),jsonIn))
		{
			std::cout<<jsonIn.toStyledString()<<std::endl;
			moteur->ReadCommand(jsonIn);
		}
	}
}

