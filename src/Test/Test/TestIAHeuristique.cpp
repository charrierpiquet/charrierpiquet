#include "IA.h"
#include <vector>

#include "TestIAHeuristique.h"
#include "Etat.h"
#include "Render.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Test
{
    void TestIAHeuristique ()
    {
        std::shared_ptr<Etat::State> state (new Etat::State);
        std::shared_ptr<Render::Rendu> rendu (new Render::Rendu(state,800,600,0));
        std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(state));
        
        IA::IA_heuristique ia (state, moteur);
        
        moteur->AddCommand(std::shared_ptr<Engine::LoadCommand>(new Engine::LoadCommand("Deck1","Deck2")));
        moteur->Update();
        
        sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
        window.setFramerateLimit(60);
        
        state->GetJoueurs()[0]->Draw();
        state->GetJoueurs()[0]->Draw();
        state->GetJoueurs()[0]->Draw();
        state->GetJoueurs()[0]->Draw();
        
        state->GetJoueurs()[1]->Draw();
        state->GetJoueurs()[1]->Draw();
        state->GetJoueurs()[1]->Draw();
        state->GetJoueurs()[1]->Draw();
        
        std::cout<<"tappez sur une touche pour passer a l'etape suivante"<<std::endl;
        
        while (window.isOpen())
        {
            sf::Event event;
            
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                //tester le click;
                if (event.type == sf::Event::MouseButtonPressed)
                    if (event.mouseButton.button == sf::Mouse::Left)
                        rendu->Click(event.mouseButton.x,event.mouseButton.y);
                
                if (event.type == sf::Event::KeyPressed)
                    ia.Think();
            }
                
            
            moteur->Update();
                
            window.clear(sf::Color::Black);
            rendu->Draw(window);
            //std::cout<<(int)(Foret1->GetIsTap())<<std::endl;
            window.display();
            
            if(state->GetJoueurs()[0]->GetPv() == 0)
            {
                std::cout<<"Le joueur 2 gagne"<<std::endl;
                window.close();
            }
            if(state->GetJoueurs()[1]->GetPv() == 0)
            {
                std::cout<<"Le joueur 1 gagne"<<std::endl;
                window.close();
            }
        }
        
    }
} 