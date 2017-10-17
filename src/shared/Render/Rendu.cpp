#include "Rendu.h"
#include "State.h"

namespace Render {
    
    Rendu::Rendu (std::weak_ptr<Etat::State> etat, int x, int y):
        cimetiere1("Cimetiere 1", true,0,0,x/4,y/3),
        cimetiere2("Cimetiere 2", true,0,2*y/3,x/4,y/3),
        bf21("BF Terrain 2", false,x/4,0,x/2,y/6),
        bf22("BF Creatures 2", false, x/4,y/6,x/2,y/6), 
        stack("Pile", false, x/4,2*y/6,x/2,y/6), 
        bf12("BF Creatures 1", false,x/4,3*y/6,x/2,y/6),
        bf11("BF Terrains 1", false,x/4,4*y/6,x/2,y/6),
        hand("BF Terrains 1", false,x/4,5*y/6,x/2,y/6),
        listCapa("Capacites",true,7*x/8,2*y/3,x/8,y/3)
    {
        state = etat;
        dimensionX = x;
        dimensionY = y;
        
        // init du fond
        sf::Texture texture;
        if (!texture.loadFromFile("..\\..\\..\\res\\Fond.png"))
        {
            // erreur
        }
        sprite.setTexture(texture);
        sprite.setPosition(0,0);
        
        sf::Font font;
        if (!=font.loadFromFile("..\\..\\..\\res\\police.ttf"))
        {
            // erreur
        }
        
        txt_etat.setFont(font);
        txt_etat.setPosition(0, 1/3*y);
        
        txt_nomSelect.setFont(font);
        txt_nomSelect.setPosition(3/4*x, 0);
        
        txt_Oracle.setFont(font);
        txt_Oracle.setPosition(3/4*x, 1/6*y);
        
        txt_instruction.setFont(font);
        txt_instruction.setPosition(3/4*x, 3/6*y);
        
        
    }
    
    void Rendu::Click(int x, int y)
    {
        if (x >= cimetiere1.GetX() && x <= cimetiere1.GetX + cimetiere1.GetWidth()
         && y >= cimetiere1.GetY() && y <= cimetiere1.GetY + cimetiere1.GetHeight())
            selectedCard = cimetiere1.Click(x,y);
        
        else if (x >= cimetiere2.GetX() && x <= cimetiere2.GetX + cimetiere2.GetWidth()
         && y >= cimetiere2.GetY() && y <= cimetiere2.GetY + cimetiere2.GetHeight())
            selectedCard = cimetiere2.Click(x,y);
        
        else if (x >= bf21.GetX() && x <= bf21.GetX + bf21.GetWidth()
         && y >= bf21.GetY() && y <= bf21.GetY + bf21.GetHeight())
            selectedCard = bf21.Click(x,y);
        
        else if (x >= bf22.GetX() && x <= bf22.GetX + bf22.GetWidth()
         && y >= bf22.GetY() && y <= bf22.GetY + bf22.GetHeight())
            selectedCard = bf22.Click(x,y);
        
        else if (x >= stack.GetX() && x <= stack.GetX + stack.GetWidth()
         && y >= stack.GetY() && y <= stack.GetY + stack.GetHeight())
            selectedCard = stack.Click(x,y);
        
        else if (x >= bf12.GetX() && x <= bf12.GetX + bf12.GetWidth()
         && y >= bf12.GetY() && y <= bf12.GetY + bf12.GetHeight())
            selectedCard = bf12.Click(x,y);
        
        else if (x >= bf11.GetX() && x <= bf11.GetX + bf11.GetWidth()
         && y >= bf11.GetY() && y <= bf11.GetY + bf11.GetHeight())
            selectedCard = bf11.Click(x,y);
        
        else if (x >= hand.GetX() && x <= hand.GetX + hand.GetWidth()
         && y >= hand.GetY() && y <= hand.GetY + hand.GetHeight())
            selectedCard = hand.Click(x,y);
        
        else if (x >= listCapa.GetX() && x <= listCapa.GetX + listCapa.GetWidth()
         && y >= listCapa.GetY() && y <= listCapa.GetY + listCapa.GetHeight())
            selectedCard = listCapa.Click(x,y);
    }
    
    void Rendu::Draw(sf::RenderTarget& target)
    {
        // afficher notre texture
        target->draw(sprite);
        // afficher les textes
        txt_etat.setString(
        ""
        );
        // afficher la selectedCard
        
        // draw les autres elements
        cimetiere1.Draw(target);
        cimetiere2.Draw(target);
        bf21.Draw(target);
        bf22.Draw(target);
        stack.Draw(target);
        bf12.Draw(target);
        bf11.Draw(target);
        hand.Draw(target);
        listCapa.Draw(target);
    }

}
