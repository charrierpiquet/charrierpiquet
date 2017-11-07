#include "TestRender.h"
#include "Etat.h"
#include "Render.h"

using namespace std;
using namespace Etat;
using namespace Render;

namespace Test
{
    void TestRender()
    {
        shared_ptr<State> state( new Etat::State());
        shared_ptr<Rendu> rendu (new Rendu(state,800,600));
        bool needActu =true;

        // creer l'etat

        // Creation d'une carte
        //création d'Iles (terrains de base)
        int identifiant = 0;
        
        shared_ptr<Cout> coutTerrain(new Cout);
        coutTerrain->SetCost();
        
        vector<shared_ptr<Capacite> > capa;
        
        shared_ptr<Carte> Foret1(new Carte(true,true,false,false,"Foret",*coutTerrain,capa,identifiant++,0));
        Foret1->SetOracle("ceci est une foret \ntap : ajoutez (G) a votre reserve\nune foret est un terrain\nun terrain est incolore");
        state->AddCardBattlefield(Foret1);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        shared_ptr<Carte> Marais1(new Carte(true,true,false,false,"Marais",*coutTerrain,capa,identifiant++,0));
        Marais1->SetOracle("ceci est un marais \ntap : ajoutez (B) a votre reserve\nun marais est un terrain\nun terrain est incolore");
        state->AddCardBattlefield(Marais1);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        shared_ptr<Carte> Ile2(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,1));
        Ile2->SetIsTap(true);
        Ile2->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
        state->AddCardBattlefield(Ile2);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        shared_ptr<Carte> Ile3(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,0));
        Ile3->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
        state->GetJoueurs()[0]->AddCardHand(Ile3);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        shared_ptr<Carte> Ile4(new Etat::Carte(true,true,false,false,"Ile",*coutTerrain,capa,identifiant++,1));
        Ile4->SetOracle("ceci est une ile \ntap : ajoutez (U) a votre reserve\nune ile est un terrain\nun terrain est incolore");
        state->GetJoueurs()[1]->AddCardGraveyard(Ile4);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;

        //Création d'Ours (Créatures de base)
        shared_ptr<Cout> coutOurs (new Cout); coutOurs->SetCost(1,0,0,1);
        shared_ptr<Creature> Ours1(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
        Ours1->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        Ours1->SetIsTap(true);
        state->AddCardBattlefield(Ours1);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;

        shared_ptr<Creature> Ours2(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
        Ours2->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->AddCardBattlefield(Ours2);        
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;

        shared_ptr<Creature> Ours3(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,1));
        Ours3->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert\ncet ours a 2 marqueurs");
        Ours3->SetIsTap(true);
        Ours3->SetCounter(2);
        state->AddCardBattlefield(Ours3);       
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        shared_ptr<Creature> Ours4(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
        Ours4->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->GetJoueurs()[0]->AddCardGraveyard(Ours4);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        shared_ptr<Creature> Ours5(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,1));
        Ours5->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->GetJoueurs()[1]->AddCardGraveyard(Ours5);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        shared_ptr<Creature> Ours6(new Creature(2,2,false,"Ours",*coutOurs,capa,identifiant++,0));
        Ours6->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert\ncet ours a un bonus de 1");
        Ours6->SetIsTap(true);
        Ours6->SetBonusEOT(1); 
        state->AddCardBattlefield(Ours6);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        shared_ptr<Creature> Ours7(new Creature(2, 2, false, "Ours", *coutOurs, capa, identifiant++, 0));
        Ours7->SetOracle("ceci est un Ours \nun Ours est une carte de creature\nun Ours a une force de 2\n un Ours a une endurance de 2\nun Ours est vert");
        state->AddCardBattlefield(Ours7);
        //cout<<state->GetBattlefield()[0]->GetOracle()<<endl;
        //cout<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBonusEOT()<<" "<<((Creature*)state->GetBattlefield()[state->GetBattlefield().size()-1].get())->GetBlessure()<<endl;


        shared_ptr<Creature> Ours8(new Creature(2, 2, false, "Ours", *coutOurs, capa, identifiant++, 0));
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