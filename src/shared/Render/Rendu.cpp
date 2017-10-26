#include "Rendu.h"
#include "Etat.h"
#include <iostream>
#include <cstddef>

namespace Render {
    
    Rendu::Rendu (std::shared_ptr<Etat::State> etat, int x, int y):
        cimetiere1("Cimetiere 2", true,0,0,x/6,y/3),
        cimetiere2("Cimetiere 1", true,0,2*y/3,x/6,y/3),
        bf21("Terrain 2", false,x/4,0,x/2,y/6),
        bf22("Creatures 2", false, x/4,y/6,x/2,y/6), 
        stack("Pile", false, x/4,2*y/6,x/2,y/6), 
        bf12("Creatures 1", false,x/4,3*y/6,x/2,y/6),
        bf11("Terrains 1", false,x/4,4*y/6,x/2,y/6),
        hand("Hand", false,x/4,5*y/6,x/2,y/6),
        listCapa("Capacites",true,7*x/8,2*y/3,x/8,y/3)
    {
        state = etat;
        dimensionX = x;
        dimensionY = y;
        
        // init du fond
        if (!texture.loadFromFile("res/Fond.png"))
        {
            // erreur
        }
        sprite.setTexture(texture);
        sprite.setScale(dimensionX/sprite.getLocalBounds().width, dimensionY/sprite.getLocalBounds().height);
        sprite.setPosition(0,0);
        
        if (!font.loadFromFile("res/police.ttf"))
        {
            // erreur
        }
        
        txt_etat.setFont(font);
        txt_etat.setPosition(10, (1./3.)*dimensionY);
        txt_etat.setCharacterSize(18);
        
        txt_nomSelect.setFont(font);
        txt_nomSelect.setPosition((3./4.)*dimensionX+10, 0);
        txt_nomSelect.setCharacterSize(18);
        
        txt_Oracle.setFont(font);
        txt_Oracle.setPosition((3./4.)*dimensionX+10, (1./6.)*dimensionY);
        txt_Oracle.setCharacterSize(18);
        
        txt_instruction.setFont(font);
        txt_instruction.setPosition((3./4.)*dimensionX+10, (3./6.)*dimensionY);
        txt_instruction.setCharacterSize(18);
              
        txt_instruction.setString(
            "ici se trouveront les instructions\n "
            " cliquez sur une carte pour plus de\n"
            "precision\n"
            " cliquez sur les boutons pour\n"
            "acceder aux cartes suivantes");
    }
    
    void Rendu::Click(int x, int y)
    {
        if (x >= cimetiere1.GetX() && x <= cimetiere1.GetX() + cimetiere1.GetWidth()
         && y >= cimetiere1.GetY() && y <= cimetiere1.GetY() + cimetiere1.GetHeight())
            selectedCard = cimetiere1.Click(x,y);
        
        else if (x >= cimetiere2.GetX() && x <= cimetiere2.GetX() + cimetiere2.GetWidth()
         && y >= cimetiere2.GetY() && y <= cimetiere2.GetY() + cimetiere2.GetHeight())
            selectedCard = cimetiere2.Click(x,y);
        
        else if (x >= bf21.GetX() && x <= bf21.GetX() + bf21.GetWidth()
         && y >= bf21.GetY() && y <= bf21.GetY() + bf21.GetHeight())
            selectedCard = bf21.Click(x,y);
        
        else if (x >= bf22.GetX() && x <= bf22.GetX() + bf22.GetWidth()
         && y >= bf22.GetY() && y <= bf22.GetY() + bf22.GetHeight())
            selectedCard = bf22.Click(x,y);
        
        else if (x >= stack.GetX() && x <= stack.GetX() + stack.GetWidth()
         && y >= stack.GetY() && y <= stack.GetY() + stack.GetHeight())
            selectedCard = stack.Click(x,y);
        
        else if (x >= bf12.GetX() && x <= bf12.GetX() + bf12.GetWidth()
         && y >= bf12.GetY() && y <= bf12.GetY() + bf12.GetHeight())
            selectedCard = bf12.Click(x,y);
        
        else if (x >= bf11.GetX() && x <= bf11.GetX() + bf11.GetWidth()
         && y >= bf11.GetY() && y <= bf11.GetY() + bf11.GetHeight())
            selectedCard = bf11.Click(x,y);
        
        else if (x >= hand.GetX() && x <= hand.GetX() + hand.GetWidth()
         && y >= hand.GetY() && y <= hand.GetY() + hand.GetHeight())
            selectedCard = hand.Click(x,y);
        
        else if (x >= listCapa.GetX() && x <= listCapa.GetX() + listCapa.GetWidth()
         && y >= listCapa.GetY() && y <= listCapa.GetY() + listCapa.GetHeight())
            selectedCard = listCapa.Click(x,y);
    }
    
    void Rendu::Draw(sf::RenderTarget& target)
    {
        // afficher notre texture
        target.draw(sprite);

        // afficher les textes d'etat
        sf::String str = "";
        str += "\nPV : " + std::to_string(state->GetJoueurs()[1-state->GetPriority()]->GetPv());   
        str += "\nMain : " + std::to_string(state->GetJoueurs()[1-state->GetPriority()]->GetHand().size());
        str += "\nDeck : " + std::to_string(state->GetJoueurs()[1-state->GetPriority()]->GetLibrary().size());
        str += "\nPhase : " +state->GetPhaseName();
        str += "\nDeck : " + std::to_string(state->GetJoueurs()[state->GetPriority()]->GetLibrary().size());
        str += "\nMain : " +std::to_string(state->GetJoueurs()[state->GetPriority()]->GetHand().size());
        str += "\nPV : " + std::to_string(state->GetJoueurs()[state->GetPriority()]->GetPv());
        txt_etat.setString(str);
        
        target.draw(txt_etat);
        target.draw(txt_instruction);
                    
        // afficher la selectedCard
        if (selectedCard != nullptr)
        {
            txt_nomSelect.setString(selectedCard->GetName());
            target.draw(txt_nomSelect);

            // afficher le texte oracle
            //std::cout<<selectedCard->GetOracle()<<std::endl;
            txt_Oracle.setString(selectedCard->GetOracle());
            target.draw(txt_Oracle);
        }  
        // draw les autres elements
        cimetiere1.Actu(Conv<Etat::Carte>(state->GetJoueurs()[1-state->GetPriority()]->GetGraveyard()));
        cimetiere1.Draw(target);
        
        std::vector<std::shared_ptr<Etat::Objet> > bf1, bf2;
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++)
            if (state->GetBattlefield()[i]->GetIndJoueur() == 1-state->GetPriority())
            {
                if (state->GetBattlefield()[i]->GetIsCreature())
                    bf2.push_back(state->GetBattlefield()[i]);
                else
                    bf1.push_back(state->GetBattlefield()[i]);
            }
        
        bf21.Actu(bf1);
        bf21.Draw(target);
        bf22.Actu(bf2);
        bf22.Draw(target);
        
        stack.Actu(state->GetPile());
        stack.Draw(target);
        
        bf1.clear(); bf2.clear();
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++)
            if (state->GetBattlefield()[i]->GetIndJoueur() == state->GetPriority())
            {
                if (state->GetBattlefield()[i]->GetIsCreature())
                    bf2.push_back(state->GetBattlefield()[i]);
                else
                    bf1.push_back(state->GetBattlefield()[i]);
            }
        
        bf12.Actu(bf2);
        bf12.Draw(target);
         
        bf11.Actu(bf1);
        bf11.Draw(target);

        //tampon = std::vector<std::shared_ptr<Etat::Objet> >(state->GetJoueurs()[state->GetPriority()]->GetHand().begin(),state->GetJoueurs()[state->GetPriority()]->GetHand().end());       
        hand.Actu(Conv<Etat::Carte>(state->GetJoueurs()[state->GetPriority()]->GetHand()));
        hand.Draw(target);        
        
        //tampon = std::vector<std::shared_ptr<Etat::Objet> >(state->GetJoueurs()[state->GetPriority()]->GetGraveyard().begin(),state->GetJoueurs()[state->GetPriority()]->GetGraveyard().end());     
        cimetiere2.Actu(Conv<Etat::Carte>(state->GetJoueurs()[state->GetPriority()]->GetGraveyard()));
        cimetiere2.Draw(target);
        
        if (selectedCard != nullptr)
        {
            //tampon = std::vector<std::shared_ptr<Etat::Objet> >(std::static_pointer_cast<Etat::Carte>(selectedCard)->GetAbility().begin(),std::static_pointer_cast<Etat::Carte>(selectedCard)->GetAbility().end());
            listCapa.Actu(Conv<Etat::Capacite>(std::static_pointer_cast<Etat::Carte>(selectedCard)->GetAbility()));
            listCapa.Draw(target);
            // on affiche le cout que pour les cartes
            if (!selectedCard->GetIsCapacite())
            {
                int compteur = 0;
                sf::Sprite cout;
                sf::Texture ttCout;
                
                if (!ttCout.loadFromFile("res/mana_noir.png"))
                {   }
                cout.setTexture(ttCout);
                cout.setScale(18./cout.getTextureRect().width,18./cout.getTextureRect().height);
                for(int i = 0 ; i < std::static_pointer_cast<Etat::Carte>(selectedCard)->GetCost().GetBlack();i++)
                {
                    cout.setPosition(3./4.*dimensionX + 20*compteur,20);
                    compteur++;
                    target.draw(cout);
                }
                if (!ttCout.loadFromFile("res/mana_bleu.png"))
                {   }
                cout.setTexture(ttCout);
                cout.setScale(18./cout.getTextureRect().width,18./cout.getTextureRect().height);
                for(int i = 0 ; i < std::static_pointer_cast<Etat::Carte>(selectedCard)->GetCost().GetBlue();i++)
                {
                    cout.setPosition(3./4.*dimensionX + 20*compteur,20);
                    compteur++;
                    target.draw(cout);
                }
                if (!ttCout.loadFromFile("res/mana_vert.png"))
                {   }
                cout.setTexture(ttCout);
                cout.setScale(18./cout.getTextureRect().width,18./cout.getTextureRect().height);
                for(int i = 0 ; i < std::static_pointer_cast<Etat::Carte>(selectedCard)->GetCost().GetGreen();i++)
                {
                    cout.setPosition(3./4.*dimensionX + 20*compteur,20);
                    compteur++;
                    target.draw(cout);
                }
                
                if(std::static_pointer_cast<Etat::Carte>(selectedCard)->GetCost().GetInc() > 0)
                {
                    if(!ttCout.loadFromFile("res/"+std::to_string(std::static_pointer_cast<Etat::Carte>(selectedCard)->GetCost().GetInc())+".png"))
                    {   }
                    cout.setTexture(ttCout);
                    cout.setScale(18./cout.getTextureRect().width,18./cout.getTextureRect().height);
                    cout.setPosition(3./4.*dimensionX + 20*compteur,20);
                    target.draw(cout);
                }
            }
        }
        // affichage manapools pas opti mais plus pratique
        nb.setFont(font);
        nb.setCharacterSize(20);
        
        for (int i = 0 ; i < 2 ; i++)
        {   
            int j = 0;
            if(!ttMp.loadFromFile("res/multi.png"))
            {   }
            mp.setTexture(ttMp);
            mp.setScale(20./mp.getTextureRect().width,20./mp.getTextureRect().height);
            mp.setPosition(dimensionX*1/6 +10 ,10 +j*24+ i*2./3.*dimensionY);
            target.draw(mp);
            j++;
            
            if(!ttMp.loadFromFile("res/mana_noir.png"))
            {   }
            mp.setTexture(ttMp);
            mp.setScale(20./mp.getTextureRect().width,20./mp.getTextureRect().height);
            mp.setPosition(dimensionX*1/6 +10 ,10 +j*24+ i*2./3.*dimensionY);
            target.draw(mp);
            j++;
            
            if(!ttMp.loadFromFile("res/mana_bleu.png"))
            {   }
            mp.setTexture(ttMp);
            mp.setScale(20./mp.getTextureRect().width,20./mp.getTextureRect().height);
            mp.setPosition(dimensionX*1/6 +10 ,10 +j*24+ i*2./3.*dimensionY);
            target.draw(mp);
            j++;
            
            if(!ttMp.loadFromFile("res/mana_vert.png"))
            {   }
            mp.setTexture(ttMp);
            mp.setScale(20./mp.getTextureRect().width,20./mp.getTextureRect().height);
            mp.setPosition(dimensionX*1/6 +10 ,10 +j*24+ i*2./3.*dimensionY);
            target.draw(mp);
            j++;
            
            if(!ttMp.loadFromFile("res/inc.png"))
            {   }
            mp.setTexture(ttMp);
            mp.setScale(20./mp.getTextureRect().width,20./mp.getTextureRect().height);
            mp.setPosition(dimensionX*1/6 +10 ,10 +j*24+ i*2./3.*dimensionY);
            target.draw(mp);
            
            nb.setString(
            std::to_string(state->GetJoueurs()[1-state->GetPriority()]->GetManaPool()->GetMulti())+"\n"+
            std::to_string(state->GetJoueurs()[1-state->GetPriority()]->GetManaPool()->GetBlack())+"\n"+
            std::to_string(state->GetJoueurs()[1-state->GetPriority()]->GetManaPool()->GetBlue())+"\n"+
            std::to_string(state->GetJoueurs()[1-state->GetPriority()]->GetManaPool()->GetGreen())+"\n"+
            std::to_string(state->GetJoueurs()[1-state->GetPriority()]->GetManaPool()->GetInc()));
            nb.setPosition(dimensionX*1/6 + 30,10 + i*2./3.*dimensionY);
            target.draw(nb);
        }
                
    }
    
    template<typename T>
    std::vector<std::shared_ptr<Etat::Objet> > Rendu::Conv(std::vector<std::shared_ptr<T> > data)
    {
        std::vector<std::shared_ptr<Etat::Objet> > tampon (data.begin(),data.end());
        return tampon;        
    }

}
