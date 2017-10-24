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
        this->nom.setString(nom);
        this->nom.setCharacterSize(12);
        if(!isVertical)
            this->nom.rotate(90);
        
        if (!textureB.loadFromFile("res/Bouton.png"))
        {
            // erreur
        }
        b1.setTexture(textureB);
        b2.setTexture(textureB);
        if (!isVertical)
        {   b1.setRotation(270);
            b1.setPosition(this->x+20 -b1.getLocalBounds().height, this->y +b1.getLocalBounds().width);
            //b1.setOrigin(b1.getLocalBounds().width/2., b1.getLocalBounds().height/2.);
            
            //b1.move(b1.getLocalBounds().width/2.,b1.getLocalBounds().height/2. );
            b2.setRotation(90);
            b2.setPosition(this->x+this->width-b2.getLocalBounds().width + b2.getLocalBounds().width/2., this->y );
            //b2.setOrigin(b2.getLocalBounds().width/2.,b2.getLocalBounds().height/2.);
            
            //b2.move(b2.getLocalBounds().width/2.,b2.getLocalBounds().height/2. );
        }
        else
        {
            b1.setPosition(this->x, this->y+20);
            //b1.setOrigin(b1.getLocalBounds().left + b1.getLocalBounds().width/2.,b1.getLocalBounds().top + b1.getLocalBounds().height/2.);
            //b1.move(b1.getLocalBounds().width/2.,b1.getLocalBounds().height/2. );
            b2.setRotation(180);
            b2.setPosition(this->x + b2.getLocalBounds().width, this->y+this->height);
            //b2.setOrigin(b2.getLocalBounds().left + b2.getLocalBounds().width/2.,b2.getLocalBounds().top + b2.getLocalBounds().height/2.);
            
            //b2.move(b2.getLocalBounds().width/2.,b2.getLocalBounds().height/2. );
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
                    sf::Texture tt;
                    if (!tt.loadFromFile("res/cartes/" + listeCartes[i]->GetName() + ".png"))            
                    {
                        // erreur
                    }
                    else
                    {
                        texture.push_back(tt);

                        std::shared_ptr<sf::Sprite> sprite (new sf::Sprite());
                        
                        sprite->setTexture(texture[texture.size()-1]);                
                        
                        sprite->setPosition(x -40 + height*(i-ind_dbt)+ sprite->getLocalBounds().width/2., y+height/2.);
                        sprite->setScale(0.3f,0.3f);
                        sprite->setOrigin(sprite->getLocalBounds().width/2.,sprite->getLocalBounds().height/2.);
                        
                        
                        if (!listeCartes[i]->GetIsCapacite())
                            if (std::static_pointer_cast<Etat::Carte>(listeCartes[i])->GetIsTap())
                                sprite->setRotation(90);

                        //sprite->move(sprite->getLocalBounds().width/2.,sprite->getLocalBounds().height/2. );
                        spriteCarte.push_back(sprite);
                    }        
                }
        }
        else
        { 
            for(unsigned int i=0 ; i < listeCartes.size(); i++) //Affichage du cimetière?
                if (i >=  ind_dbt && i < ind_dbt + nb_elem)
                {
                    std::shared_ptr<sf::Text> txt(new sf::Text());
                    txt->setFont(font);
                    txt->setCharacterSize(12);
                    txt->setString(listeCartes[i]->GetName()); 
                    txt->setPosition(x,y+40 + 20*(i - ind_dbt));
                    spriteCarte.push_back(txt);
                }
        }         
    }    
    
    void Editeur::Draw(sf::RenderTarget& target)
    {
        target.draw(b1);
        target.draw(b2);
        target.draw(nom);
        for(unsigned int i = 0 ; i < spriteCarte.size() ; i ++)
            target.draw(*spriteCarte[i]);
    }
    
    std::shared_ptr<Etat::Objet> Editeur::Click(int x, int y)
    {
        std::cout<<x << " "<< y << " " <<b1.getPosition().x <<" "<< b1.getPosition().x + b1.getLocalBounds().width<< " "<<b1.getPosition().y + b1.getLocalBounds().height<< " "<< b1.getPosition().y<<" "  <<b2.getPosition().x << " "<< b2.getPosition().y<<" " << b2.getPosition().x + b2.getLocalBounds().width<< " "<<b2.getPosition().y + b2.getLocalBounds().height<< " "<< std::endl;
        
        if (y > b1.getPosition().y && y < b1.getPosition().y + b1.getLocalBounds().height
            && x > b1.getPosition().x && x < b1.getPosition().x + b1.getLocalBounds().width)
                SetIndDbt(ind_dbt - 1);
        else if (y > b2.getPosition().y && y < b2.getPosition().y + b2.getLocalBounds().height
            && x > b2.getPosition().x && x < b2.getPosition().x + b2.getLocalBounds().width)
                SetIndDbt(ind_dbt + 1);
        
        if (isVertical && (y-this->y - 40)/20 < (int)listeCartes.size())
                return listeCartes[(y - this->y - 40)/20];
        else if ( !isVertical && (x - this->x - 40)/height < (int)listeCartes.size())
                return listeCartes[(x - this->x - 40)/height];
        
        return nullptr;
    }
    
    void Editeur::SetIndDbt(int value)
    {
        std::cout<<"click"<<std::endl;
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
