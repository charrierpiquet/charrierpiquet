#include "Editeur.h"
#include "Etat/Objet.h"
#include "Etat/Carte.h"
#include <cstddef>
#include <iostream>

namespace Render
{
    Editeur::Editeur(std::string nom, bool orientation, int x, int y, int width, int height)
    {
        
        this->isVertical = orientation;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        
        ind_dbt = 0;
        if (!isVertical)
            nb_elem = (width -60)/ height;
        else
            nb_elem = (height -60) / 20;
       
        if (!font.loadFromFile("res/police.ttf"))
        {
            // erreur
        }
        
        this->nom.setFont(font);
        this->nom.setPosition(this->x, this->y);
        if(!isVertical)
            this->nom.rotate(90);
        
        if (!textureB.loadFromFile("res/Bouton.png"))
        {
            // erreur
        }
        b1.setTexture(textureB);
        b2.setTexture(textureB);
        if (!isVertical)
        {
            b1.setPosition(this->x+20,this->y);
            b2.setPosition(this->x+this->width-20,this->y);
            b2.rotate(180);
        }
        else
        {
            b1.setPosition(this->x,this->y+20);
            b1.rotate(90);
            b2.setPosition(this->x,this->y+this->height-20);
            b2.rotate(270);
        }        
    }
    
    void Editeur::Actu(std::vector<std::shared_ptr<Etat::Objet> > list_carte)
    {
        spriteCarte.clear();
        listeCartes = list_carte;
        texture.clear();
        if (!isVertical)
        {
            for(unsigned int i=0 ; i < listeCartes.size(); i++)
                if (i >=  ind_dbt && i < ind_dbt + nb_elem)
                {
                    std::shared_ptr<sf::Texture> tt;
                    if (!tt->loadFromFile("res/cartes/" + listeCartes[i]->GetName() + ".png"))            
                    {
                        // erreur
                    }
                    texture.push_back(tt);
                                       
                    std::shared_ptr<sf::Sprite> sprite;
                    
                    std::cout<<texture.size()<< " " << i<< " "<< in_dbt << std::endl; 
                    sprite->setTexture(*(texture[i-ind_dbt]));
                    
                    if (!listeCartes[i]->GetIsCapacite())
                        if (std::static_pointer_cast<Etat::Carte>(listeCartes[i])->GetIsTap())
                            sprite->rotate(90);
                    // setScale ?
                    
                    sprite->setPosition(x + 40 + height*(i-ind_dbt), y);
                    
                    spriteCarte.push_back(sprite);
                            
                }
        }
        else
        {
            for(unsigned int i=0 ; i < listeCartes.size(); i++)
                if (i >=  ind_dbt && i < ind_dbt + nb_elem)
                {
                    std::shared_ptr<sf::Text> txt;
                    txt->setFont(font);
                    txt->setString(listeCartes[i]->GetName());
                    txt->setPosition(x,y+40 + 20*(i - ind_dbt));
                    spriteCarte.push_back(txt);
                }
        }
               
    }
    
    void Editeur::Draw(sf::RenderTarget& target)
    {
        for(unsigned int i = 0 ; i < spriteCarte.size() ; i ++)
            target.draw(*spriteCarte[i]);
    }
    
    std::shared_ptr<Etat::Objet> Editeur::Click(int x, int y)
    {
        if (isVertical)
        {
            if (y > 20 && y < 40)
                SetIndDbt(ind_dbt - 1);
            else if (y > height - 20 && y < height)
                SetIndDbt(ind_dbt + 1);
            else
                return listeCartes[(y - this->y - 40)/20];
        }
        else
        {
            if (x > 20 && x < 40)
                SetIndDbt(ind_dbt - 1);
            else if (x > width - 20 && x < width)
                SetIndDbt(ind_dbt + 1);
            else
                return listeCartes[(x - this->x - 40)/height];
        }
        return nullptr;
    }
    
    void Editeur::SetIndDbt(int value)
    {
        if (listeCartes.size() < nb_elem)
            ind_dbt = 0;
        else if (value < 0)
            ind_dbt = 0;
        else if (value > (int)(listeCartes.size() - nb_elem))
            ind_dbt = listeCartes.size() - nb_elem;
        else
            nb_elem = value;
    }
    
    
    int Editeur::GetX() const
    {
        return x;
    }
    int Editeur::GetY() const
    {
        return y;
    }
    int Editeur::GetWidth() const
    {
        return width;
    }
    int Editeur::GetHeight() const
    {
        return height;
    }
    
    int Editeur::GetIndDbt() const
    {
        return ind_dbt;
    }
    int Editeur::GetNbElem() const
    {
        return nb_elem;
    }
    
    bool Editeur::GetIsVertical() const
    {
        return isVertical;
    }
    std::vector<std::shared_ptr<Etat::Objet> > Editeur::GetCartes() const
    {
        return listeCartes;
    }
    
}
