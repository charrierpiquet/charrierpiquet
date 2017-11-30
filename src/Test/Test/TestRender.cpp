#include "TestRender.h"
#include "Etat.h"
#include "Render.h"
#include <SFML/Graphics.hpp>

namespace Test
{
    void TestRender()
    {
        std::shared_ptr<Etat::State> state(new Etat::State());
        std::shared_ptr<Render::Rendu> rendu (new Render::Rendu(state,800,600,0));
        bool needActu =true;

        // creer l'etat

        // Creation d'une carte
        //création d'Iles (terrains de base)
        int identifiant = 0;
        
        std::shared_ptr<Etat::Cout> coutTerrain(new Etat::Cout());
        coutTerrain->SetCost();
        
        std::vector<std::shared_ptr<Etat::Active> > capa;
        
        std::shared_ptr<Etat::Carte> Foret1(new Etat::Carte(true,true,false,false,"Foret",coutTerrain,capa,identifiant++,0));
        Foret1->SetOracle("ceci est une foret \ntap : ajoutez (G) a votre reserve\nune foret est un terrain\nun terrain est incolore");
        state->AddCardBattlefield(Foret1);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        std::shared_ptr<Etat::Carte> Marais1(new Etat::Carte(true,true,false,false,"Marais",coutTerrain,capa,identifiant++,0));
        Marais1->SetOracle("ceci est un marais \ntap : ajoutez (B) a votre reserve\nun marais est un terrain\nun terrain est incolore");
        state->AddCardBattlefield(Marais1);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        std::shared_ptr<Etat::Carte>  Ile2(new Etat::Carte(true,true,false,false,"Ile",coutTerrain,capa,identifiant++,1));
        Ile2->SetIsTap(true);
        Ile2->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
        state->AddCardBattlefield(Ile2);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        std::shared_ptr<Etat::Carte>  Ile3(new Etat::Carte(true,true,false,false,"Ile",coutTerrain,capa,identifiant++,0));
        Ile3->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
        state->GetJoueurs()[0]->AddCardHand(Ile3);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        std::shared_ptr<Etat::Carte>  Ile4(new Etat::Carte(true,true,false,false,"Ile",coutTerrain,capa,identifiant++,1));
        Ile4->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
        state->GetJoueurs()[1]->AddCardGraveyard(Ile4);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        //Création d'Ours (Créatures de base)
        std::shared_ptr<Etat::Cout> coutOurs (new Etat::Cout); coutOurs->SetCost(1,0,0,1);
        std::shared_ptr<Etat::Creature>  Ours1(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,0));
        Ours1->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        Ours1->SetIsTap(true);
        state->AddCardBattlefield(Ours1);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;

        std::shared_ptr<Etat::Creature>  Ours2(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,0));
        Ours2->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->AddCardBattlefield(Ours2);        
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;

        std::shared_ptr<Etat::Creature>  Ours3(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,1));
        Ours3->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert\ncet ours a 2 marqueurs");
        Ours3->SetIsTap(true);
        Ours3->SetCounter(2);
        state->AddCardBattlefield(Ours3);       
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        std::shared_ptr<Etat::Creature>  Ours4(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,0));
        Ours4->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->GetJoueurs()[0]->AddCardGraveyard(Ours4);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        std::shared_ptr<Etat::Creature> Ours5(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,1));
        Ours5->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->GetJoueurs()[1]->AddCardGraveyard(Ours5);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


       std::shared_ptr<Etat::Creature>  Ours6(new Etat::Creature(2,2,false,"Ours",coutOurs,capa,identifiant++,0));
        Ours6->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert\ncet ours a un bonus de 1");
        Ours6->SetIsTap(true);
        Ours6->SetBonusEOT(1); 
        state->AddCardBattlefield(Ours6);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        std::shared_ptr<Etat::Creature>  Ours7(new Etat::Creature(2, 2, false, "Ours", coutOurs, capa, identifiant++, 0));
        Ours7->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->AddCardBattlefield(Ours7);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        std::shared_ptr<Etat::Creature>  Ours8(new Etat::Creature(2, 2, false, "Ours", coutOurs, capa, identifiant++, 0));
        Ours8->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert\ncet ours a 1 blessure");
        Ours8->SetBlessure(1);
        state->AddCardBattlefield(Ours8);
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //state->GetBattlefield()[state->GetBattlefield().size()-1]->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->GetBattlefield()[state->GetBattlefield().size()-1]->SetIsTap(true);
         
        //Rendu	
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