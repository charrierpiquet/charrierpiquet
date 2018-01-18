#include "TestReplay.h"
#include <json/json.h>
#include <fstream>
#include <iostream>

#include "Ai.h"
#include <vector>
#include "Etat.h"
#include "Render.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Test
{
    void TestReplay()
    {
        
        std::vector<std::string> Decks;
        Decks.push_back("Deck1");Decks.push_back("Deck2");
        std::shared_ptr<Etat::State> state (new Etat::State(Decks));
        std::shared_ptr<Render::Rendu> rendu (new Render::Rendu(state,800,600,0));
        std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(state));
        Json::Value val;
        std::ifstream file ("replay.txt");
        file >> val;
        file.close();
        int compteur = 0;
        sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
        window.setFramerateLimit(60);
        std::weak_ptr<Engine::Moteur> null_weak_ptr;

        
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
                {
                    if (compteur>(int)val.size())
                        window.close();
                    for (unsigned int i = 0 ; i < val[compteur].size() ; i++)
                    {
                        std::shared_ptr<Engine::Command> cmd;
                        //std::cout<<val[compteur]<<std::endl;
                        std::string type =  val[compteur][i]["typeCmd"].asString();
                        if (type.compare("Active")==0)
                            cmd = std::shared_ptr<Engine::CommandActive>((new Engine::CommandActive())->Deserialize(val[compteur][i]));
                        else if (type.compare("Attack")==0)
                            cmd = std::shared_ptr<Engine::CommandAttack>((new Engine::CommandAttack())->Deserialize(val[compteur][i]));
                        else if (type.compare("Block")==0)
                            cmd = std::shared_ptr<Engine::CommandBlock>((new Engine::CommandBlock())->Deserialize(val[compteur][i]));
                        else if (type.compare("Cast")==0)
                            cmd = std::shared_ptr<Engine::CommandCast>((new Engine::CommandCast())->Deserialize(val[compteur][i]));
                        else if (type.compare("Clean")==0)
                            cmd = std::shared_ptr<Engine::CommandClean>((new Engine::CommandClean())->Deserialize(val[compteur][i]));
                        else if (type.compare("Die")==0)
                            cmd = std::shared_ptr<Engine::CommandDie>((new Engine::CommandDie())->Deserialize(val[compteur][i]));
                        else if (type.compare("Discard")==0)
                            cmd = std::shared_ptr<Engine::CommandDiscard>((new Engine::CommandDiscard())->Deserialize(val[compteur][i]));
                        else if (type.compare("Draw")==0)
                            cmd = std::shared_ptr<Engine::CommandDraw>((new Engine::CommandDraw())->Deserialize(val[compteur][i]));
                        else if (type.compare("Paye")==0)
                            cmd = std::shared_ptr<Engine::CommandPaye>((new Engine::CommandPaye())->Deserialize(val[compteur][i]));
                        else if (type.compare("Phase")==0)
                            cmd = std::shared_ptr<Engine::CommandPhase>((new Engine::CommandPhase())->Deserialize(val[compteur][i]));
                        else if (type.compare("Priority")==0)
                            cmd = std::shared_ptr<Engine::CommandPriority>((new Engine::CommandPriority())->Deserialize(val[compteur][i]));
                        else if (type.compare("ResolveCapa")==0)
                        {
                            cmd = std::shared_ptr<Engine::CommandResolveCapa>((new Engine::CommandResolveCapa())->Deserialize(val[compteur][i]));
                            std::static_pointer_cast<Engine::CommandResolveCapa>(cmd)->SetEngine(null_weak_ptr);
                        }
                        else if (type.compare("ResolveCard")==0)
                        {
                            cmd = std::shared_ptr<Engine::CommandResolveCard>((new Engine::CommandResolveCard())->Deserialize(val[compteur][i]));
                            std::static_pointer_cast<Engine::CommandResolveCard>(cmd)->SetEngine(null_weak_ptr);
                        }
                        else if (type.compare("SolveCombat")==0)
                            cmd = std::shared_ptr<Engine::CommandSolveCombat>((new Engine::CommandSolveCombat())->Deserialize(val[compteur][i]));
                        else if (type.compare("Tour")==0)
                            cmd = std::shared_ptr<Engine::CommandTour>((new Engine::CommandTour())->Deserialize(val[compteur][i]));
                        else if (type.compare("Untap")==0)
                            cmd = std::shared_ptr<Engine::CommandUntap>((new Engine::CommandUntap())->Deserialize(val[compteur][i]));
                        else if (type.compare("VideMp")==0)
                            cmd = std::shared_ptr<Engine::CommandVideMp>((new Engine::CommandVideMp())->Deserialize(val[compteur][i]));
                        else
                            std::cout<<"Erreur type de commande non reconnu"<<std::endl;
                        
                        moteur->AddCommand(cmd);
                    }           
                    moteur->Update();
                    compteur++;
                }
                    
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