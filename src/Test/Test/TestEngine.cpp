#include <vector>
//#include "Capacite.h"
#include "TestEngine.h"
#include "Etat.h"
#include "Render.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Test
{
    int TestEngine()
    {
        int result = 0;
                std::vector<std::string> Decks;
        Decks.push_back("Deck1");Decks.push_back("Deck2");
        std::shared_ptr<Etat::State> state (new Etat::State(Decks));
        std::shared_ptr<Render::Rendu> rendu (new Render::Rendu(state,800,600,0));
        Engine::Moteur moteur(state);
        
        sf::RenderWindow window(sf::VideoMode(800,600),"Sorcellerie, le Regroupement",sf::Style::Close);
        window.setFramerateLimit(60);
        
        std::vector<std::shared_ptr<Etat::Capacite> > capa;
        int identifiant = 0;
        // positionner un ours en face (eventuellement deux terrains pour dire qu'il avait le droit d'avoir un ours)
        std::shared_ptr<Etat::Cout> coutOurs (new Etat::Cout(0,1,0,0,1));
        std::shared_ptr<Etat::Cout> coutnull (new Etat::Cout(0,0,0,0,0));
        
        std::shared_ptr<Etat::Creature> Ours1(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,1));
        Ours1->SetOracle("ours Adverse 2/2");
        state->AddCardBattlefield(Ours1);
        
        std::shared_ptr<Etat::Creature> Ours2(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,0));
        Ours2->SetOracle("ours Allie n1 2/2");
        Ours2->SetMalInvoc(false);
        state->AddCardBattlefield(Ours2);
        
        std::shared_ptr<Etat::Creature> Ours3(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,0));
        Ours3->SetOracle("ours Allie n2 2/2");
        Ours3->SetMalInvoc(false);
        state->AddCardBattlefield(Ours3);
        
        std::vector<std::shared_ptr<Etat::Capacite> > capa1;
        capa1.push_back(std::shared_ptr<Etat::Capacite>(new Etat::Capacite(coutnull,"green",identifiant++,0,"green",false,std::weak_ptr<Etat::Carte>())));
        std::shared_ptr<Etat::Carte> Foret1(new Etat::Carte(true,true,false,false,"Foret",coutnull,capa1,identifiant++,0));
        Foret1->SetOracle("T : add G to manapool");
        Foret1->GetAbility()[0]->SetSource(Foret1);
        state->AddCardBattlefield(Foret1);
        
        std::vector<std::shared_ptr<Etat::Capacite> > capa2;
        capa2.push_back(std::shared_ptr<Etat::Capacite>(new Etat::Capacite(coutnull,"blue",identifiant++,0,"blue",false,std::weak_ptr<Etat::Carte>())));
        std::shared_ptr<Etat::Carte> Ile1(new Etat::Carte(true,true,false,false,"Ile",coutnull,capa2,identifiant++,0));
        Ile1->SetOracle("T : add U to manapool");
        Ile1->GetAbility()[0]->SetSource(Ile1);

        state->AddCardBattlefield(Ile1);
        
        std::shared_ptr<Etat::Creature> Ours4(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,0));
        Ours4->SetOracle("ours en main");
        state->GetJoueurs()[0]->AddCardHand(Ours4);
        
        // positionner deux ours chez nous (ou un si c'est vraiment chiant)
        // positionner deux terrains chez nous (ou deux pour dire qu'on avait le droit d'avoir les ours)
        // engager deux terrains pour avoir deux mana
        // lancer un ours
        // attaquer avec le(s) ours
        // bloquer avec un ours
        // passer juqu'a la fin du tour
        std::cout<<"tappez sur une touche pour passer a l'etape suivante"<<std::endl;
        int i = -1;
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
                    i ++;
                    switch (i)
                    {
                        case 0 :
                        {
                            std::cout<<"Activation des capacites des terrains ...";
                            
                            moteur.Update();
                            if (state->GetPile().size() != 2 )
                                return 1;
                             std::cout<<" OK "<<std::endl;
                            break;
                        }
                        case 1 :
                        {
                            std::cout<<"Resolution des capacites ... ";

                            
                            moteur.Update();                            
                            if (state->GetPile().size() != 0 || 
                                state->GetJoueurs()[0]->GetManaPool()->GetBlue() != 1 || 
                                state->GetJoueurs()[0]->GetManaPool()->GetGreen() != 1 )
                                return 2;
                             std::cout<<" OK "<<std::endl;  
                            break;
                        }
                        case 2 :
                        {
                            std::cout<<"Lancement de l'ours ... ";
                            
                            moteur.Update();
                            if (state->GetPile().size() != 1 || state->GetJoueurs()[0]->GetHand().size() != 0)
                                return 3;
                            std::cout<<" OK "<<std::endl;  
                            break;
                        }
                        case 3 :
                        {
                            std::cout<<"Resolution de l'ours ...";
                            
                            moteur.Update();
                            if (state->GetPile().size() != 0)
                                return 4;
                            std::cout<<" OK "<<std::endl;
                            break;
                        }
                        case 4 :
                        {
                            std::cout<<"Declaration des Attaquants ...";
                            
                            moteur.Update();
                            if (!Ours2->GetIsTap() || !Ours3->GetIsTap())
                                return 5;
                            std::cout<<" OK "<<std::endl;
                            break;
                        }
                        case 5 :
                        {
                            std::cout<<"Declaration des bloqueurs et resolution de l'attaque ...";
                                    
                            std::vector<std::shared_ptr<Etat::Creature> > attaquant;
                            attaquant.push_back(Ours2);
                            attaquant.push_back(Ours3);
                            
                            moteur.Update();
                            if (state->GetJoueurs()[0]->GetGraveyard().size()!=1 || state->GetJoueurs()[1]->GetGraveyard().size()!=1 || state->GetJoueurs()[1]->GetPv() != 18 )
                                return 6;
                            std::cout<<" OK "<<std::endl;
                            
                            std::cout<<"The END"<<std::endl;
                            break;
                        }
                        default :
                            break;
                        }
                }
            }
                
            
            moteur.Update();
                
            window.clear(sf::Color::Black);
            rendu->Draw(window);
            //std::cout<<(int)(Foret1->GetIsTap())<<std::endl;
            window.display();
        }
        return result;
    }
}
