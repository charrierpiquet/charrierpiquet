#include "Ai.h"
#include <vector>

#include "TestRollBack.h"
#include "Etat.h"
#include "Render.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Test {

    void TestRollback() {
        std::vector<std::string> Decks;
        Decks.push_back("Deck1");
        Decks.push_back("Deck2");
        std::shared_ptr<Etat::State> state(new Etat::State(Decks));
        std::shared_ptr<Render::Rendu> rendu(new Render::Rendu(state, 800, 600, 0));
        std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(state));
        std::vector<int> pallier;
        Ai::Ia_Base ia(state, moteur);

        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->Update();
        pallier.push_back(moteur->HistoricSize());
        sf::RenderWindow window(sf::VideoMode(800, 600), "Sorcellerie, le Regroupement", sf::Style::Close);
        window.setFramerateLimit(60);


        std::cout << "tappez sur -> pour passer a l'etape suivante" << std::endl << "tappez sur <- pour passer a l'etape suivante" << std::endl;

        while (window.isOpen()) {
            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                //tester le click;
                if (event.type == sf::Event::MouseButtonPressed)
                    if (event.mouseButton.button == sf::Mouse::Left)
                        rendu->Click(event.mouseButton.x, event.mouseButton.y);

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Right) {
                        ia.Think();
                        std::cout << "Tour " << state->GetJoueurTour() << "; Phase " << state->GetPhaseName() << "; Priorite " << state->GetPriority() << std::endl;
                        pallier.push_back(moteur->HistoricSize());
                    }
                    if (event.key.code == sf::Keyboard::Left) {
                        while (moteur->HistoricSize() != pallier.back())
                            moteur->RollBack();
                        if (pallier.size() > 1)
                            pallier.pop_back();
                    }
                }

            }


            moteur->Update();

            window.clear(sf::Color::Black);
            rendu->Draw(window);
            //std::cout<<(int)(Foret1->GetIsTap())<<std::endl;
            window.display();

            if (state->GetJoueurs()[0]->GetPv() == 0) {
                std::cout << "Le joueur 2 gagne" << std::endl;
                window.close();
            }
            if (state->GetJoueurs()[1]->GetPv() == 0) {
                std::cout << "Le joueur 1 gagne" << std::endl;
                window.close();
            }
        }

    }
} 