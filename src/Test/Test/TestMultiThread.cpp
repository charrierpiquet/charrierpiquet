/*
Fonction de test du multithreading avec l'IA heuristique,
car l'IA avancée est trop gourmande en ressources actuellement.
*/
#include "Ai.h"
#include <vector>

#include "TestMultiThread.h"
//#include <thread>
//#include <mutex>
#include "Etat.h"
#include "Render.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>



namespace Test
{
	class Para
	{
		public:
		std::shared_ptr<Etat::State> GameState;
		std::mutex mutx;//(new std::mutex());
		bool process = false;
		bool close= false;
		bool set = false;
		
	} ;
	
	void ThreadMoteur (Para& Args);
    
    void TestMultiThread ()
    {
		Para Args;
		std::shared_ptr<Etat::State> state;
		std::vector<std::string> Decks;
        Decks.push_back("Deck1");Decks.push_back("Deck2");
		Args.GameState = std::shared_ptr<Etat::State>(new Etat::State(Decks));

		std::cout << "Jusqu'ici" << std::endl;
		
		std::thread moteur (&ThreadMoteur, std::ref(Args)); //création du thread moteur

		std::cout << "Tout va bien" << std::endl;

        std::shared_ptr<Render::Rendu> rendu (new Render::Rendu(state,800,600,0));
        sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
        window.setFramerateLimit(60);
        
        while (window.isOpen())
        {
            sf::Event event;

            std::cout << "La boucle!" << std::endl;
			Args.set = true;
            while (window.pollEvent(event))
            {
				
                if (event.type == sf::Event::Closed)
                {
                    window.close();
				}
                //tester le click;
                if (event.type == sf::Event::MouseButtonPressed)
                    if (event.mouseButton.button == sf::Mouse::Left)
                        rendu->Click(event.mouseButton.x,event.mouseButton.y);
                
                if (event.type == sf::Event::KeyPressed)
                {
					Args.mutx.lock();
					Args.process = true;
					Args.mutx.unlock();
                }
            }
            
            
            
                
            window.clear(sf::Color::Black);
			Args.mutx.lock(); // on verrouille l'état pour lire dedans
            rendu->Draw(window);
            Args.mutx.unlock();
			window.display();
            
            if (Args.close)
				window.close();
            
            
        }
        
    }
    
    void ThreadMoteur (Para& Args)
    {
		std::cout << "Ca va mieux" << std::endl;

        std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(Args.GameState));
        
        Ai::Ia_Heuristic ia (Args.GameState, moteur);
        
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));     
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        Args.mutx.lock();
        moteur->Update();
        Args.mutx.unlock();
        
		while(!Args.set);
        std::cout<<"appuyez sur une touche pour passer a l'etape suivante"<<std::endl;
        
        while(1)
        {
			std::cout << "Le grappin!" << std::endl;
			if (Args.process)
			{
				Args.mutx.lock();//on verrouille l'état pour écrire dedans
				Args.process = false;
				ia.Think();
				moteur->Update();
				Args.mutx.unlock();
			}
			Args.mutx.lock();
			if(Args.GameState->GetJoueurs()[0]->GetPv() == 0)
            {
                std::cout<<"Le joueur 2 gagne"<<std::endl;
                Args.close = true;
            }
            if(Args.GameState->GetJoueurs()[1]->GetPv() == 0)
            {
                std::cout<<"Le joueur 1 gagne"<<std::endl;
                Args.close = true;
            }
            Args.mutx.unlock();
        }
       
        
	}
	

} 
