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
<<<<<<< HEAD
        sf::Http::Request req1 ("user/-1",sf::Http::Request::Method::Post,obj.toStyledString());
        req1.setMethod(sf::Http::Request::Method::Post);
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


	getc(stdin);

	// on supprime le gens
        sf::Http::Request req4 ("user/"+std::to_string(id),sf::Http::Request::Method::Delete);
        rep = http.sendRequest(req4);

	// on affiche les gens connectes
        	sf::Http::Request req5 ("user/-1");
		rep = http.sendRequest(req5);
		std::cout<<"nb joueur : "<<std::endl<<rep.getBody()<<std::endl;
    }
}
=======
        sf::Http::Request req1 ("user",sf::Http::Request::Method::Put,obj.toStyledString());
        req1.setMethod(sf::Http::Request::Method::Put);
        rep = http.sendRequest(req1);
        std::cout<<rep.getBody()<<std::endl;
        int id = 0; // recuperer son identifiant
        sf::Http::Request req2 ("user/"+std::to_string(id));
        rep = http.sendRequest(req2);
        std::cout<<rep.getBody()<<std::endl;
        char a;
        do// trouver un truc pour faire des choses tant que l'on a pas appuyé sur une touche
        {
            a = std::getchar();
            // get
            // si suffisament joueurs
            //      break
            // sleep
        }while (a != 'a');
        sf::Http::Request req3 ("http://localhost:8080/user/"+std::to_string(id),sf::Http::Request::Method::Delete);
        rep = http.sendRequest(req3);
    }
}
>>>>>>> 89fd093ffbb508ed24727a92ec930da23f19dd05
