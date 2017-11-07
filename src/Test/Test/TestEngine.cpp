#include "TestEngine.h"

namespace Test
{
    int TestEngine()
    {
        std::shared_ptr<Etat::State> state( new Etat::State());
        std::shared_ptr<Render::Rendu> rendu (new Render::Rendu(state,800,600));
        bool needActu =true;
            
        sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
        window.setFramerateLimit(60);
            
        while (window.isOpen())
        {
            sf::Event event;
            
            while (window.pollEvent(event))
            {
                needActu = true;
                if (event.type == sf::Event::Closed)
                    window.close();
                //tester le click;
                if (event.type == sf::Event::MouseButtonPressed)
                    if (event.mouseButton.button == sf::Mouse::Left)
                        rendu->Click(event.mouseButton.x,event.mouseButton.y);
            }
                
            if (needActu)
            {                
                window.clear(sf::Color::Black);
                rendu->Draw(window);
                
                window.display();
                needActu = false;
            }
        }
    }
}