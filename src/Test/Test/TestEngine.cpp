#include <vector>

#include "TestEngine.h"
#include "Etat.h"
#include "Render.h"
#include <SFML/Graphics.hpp>

namespace Test
{
    int TestEngine()
    {
        std::shared_ptr<Etat::State> state( new Etat::State());
        std::shared_ptr<Render::Rendu> rendu (new Render::Rendu(state,800,600));
        bool needActu =true;
            
        sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
        window.setFramerateLimit(60);
        std::vector<std::shared_ptr<Etat::Capacite> > capa;
        int identifiant = 0;
        // positionner un ours en face (eventuellement deux terrains pour dire qu'il avait le droit d'avoir un ours)
        std::shared_ptr<Etat::Cout> coutOurs (new Etat::Cout()); coutOurs->SetCost(1,0,0,1);
        auto coutnull = new Etat::Cout(); coutnull->SetCost();
        
        std::shared_ptr<Etat::Creature> Ours1(new Etat::Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,1));
        Ours1->SetOracle("ours Adverse 2/2");
        state->AddCardBattlefield(Ours1);

        std::shared_ptr<Etat::Creature> Ours2(new Etat::Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
        Ours2->SetOracle("ours Allie n°1 2/2");
        state->AddCardBattlefield(Ours2);
        
        std::shared_ptr<Etat::Creature> Ours3(new Etat::Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
        Ours3->SetOracle("ours Allie n°2 2/2");
        state->AddCardBattlefield(Ours3);
        
        capa.push_back(new Etat::Active(*coutnull,(std::string)"green",identifiant++,0,(std::string)"green"));
        std::shared_ptr<Etat::Carte> Foret1(new Etat::Carte(true,true,false,false,"Foret",*coutnull,capa,identifiant++,0));
        Foret1->SetOracle("T : add G to manapool");
        state->AddCardBattlefield(Foret1);
        
        capa.clear();
        capa.push_back(new Etat::Active(*coutnull,"blue",identifiant++,0,"blue"));
        std::shared_ptr<Etat::Carte> Ile1(new Etat::Carte(true,true,false,false,"Ile",*coutnull,capa,identifiant++,0));
        Ile1->SetOracle("T : add U to manapool");
        state->AddCardBattlefield(Ile1);
        
        std::shared_ptr<Etat::Creature> Ours4(new Etat::Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
        Ours4->SetOracle("ours en main");
        state->GetJoueurs()[0]->AddCardHand(Ours4);
        // positionner deux ours chez nous (ou un si c'est vraiment chiant)
        // positionner deux terrains chez nous (ou deux pour dire qu'on avait le droit d'avoir les ours)
        // engager deux terrains pour avoir deux mana
        // lancer un ours
        // attaquer avec le(s) ours
        // bloquer avec un ours
        // passer juqu'a la fin du tour
        
        
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