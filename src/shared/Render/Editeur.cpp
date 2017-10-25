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
        
        sf::Text marqueurs;
        marqueurs.setCharacterSize(18);
        marqueurs.setFont(font);
        std::string str = "";
        for(unsigned int i = 0 ; i < spriteCarte.size() ; i ++)
        {
            target.draw(*spriteCarte[i]);
            // c'est pas opti mais c'étais plus pratique de faire ça ici une fois le reste fait
            if(!listeCartes[i+ind_dbt]->GetIsCapacite())
            {
                if (std::static_pointer_cast<Etat::Carte>(listeCartes[i+ind_dbt])->GetCounter() > 0)
                {
                    str = std::to_string(std::static_pointer_cast<Etat::Carte>(listeCartes[i+ind_dbt])->GetCounter());
                    marqueurs.setString(str);
                    marqueurs.setColor(sf::Color::Blue);
                    //marqueurs.setPosition(0,0);
                    marqueurs.setPosition(std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().left+5,std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().top +std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().height/2 );
                    target.draw(marqueurs);
                    //std::cout<<"on a "<<str<<"  marqueurs "<< std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().left << " " << std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().top +std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().height/2<<std::endl;
                }
                if (std::static_pointer_cast<Etat::Carte>(listeCartes[i+ind_dbt])->GetIsCreature())
                    if (std::static_pointer_cast<Etat::Creature>(listeCartes[i+ind_dbt])->GetBonusEOT() > 0)
                    {
                        str = std::to_string(std::static_pointer_cast<Etat::Creature>(listeCartes[i+ind_dbt])->GetBonusEOT());
                        marqueurs.setString(str);
                        marqueurs.setColor(sf::Color::Green);
                        marqueurs.setPosition(std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().left +25,std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().top +std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().height/2 );
                        target.draw(marqueurs);
                        str = std::to_string(std::static_pointer_cast<Etat::Creature>(listeCartes[i+ind_dbt])->GetBlessure());
                        marqueurs.setString(str);
                        marqueurs.setColor(sf::Color::Red);
                        marqueurs.setPosition(std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().left +45,std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().top +std::static_pointer_cast<sf::Sprite>(spriteCarte[i])->getGlobalBounds().height/2 );
                        target.draw(marqueurs);
                    }
            }
        }
    }
    
    std::shared_ptr<Etat::Objet> Editeur::Click(int x, int y)
    {
        /*std::cout<< "x : "<< x ;
        std::cout<< "  y : "<< y ;
        std::cout<<std::endl;
        std::cout<< "  b1x : " << b1.getPosition().x ;
        std::cout<< "  b1y : " << b1.getPosition().y;
        std::cout<< "  b1w : " << b1.getLocalBounds().width;
        std::cout<< "  b1h : " << b1.getLocalBounds().height;
        std::cout<<std::endl;
        std::cout<< "  b2x : " << b2.getPosition().x ;
        std::cout<< "  b2y : " << b2.getPosition().y;
        std::cout<< "  b2w : " << b2.getLocalBounds().width;
        std::cout<< "  b2h : " << b2.getLocalBounds().height;
        std::cout<<std::endl;*/
      
        
        if (isVertical)
        {
            if (y > b1.getPosition().y && y < b1.getPosition().y + b1.getLocalBounds().height
                && x > b1.getPosition().x && x < b1.getPosition().x + b1.getLocalBounds().width)
                SetIndDbt(ind_dbt - 1);
            else if (y < b2.getPosition().y && y > b2.getPosition().y - b2.getLocalBounds().height
                && x < b2.getPosition().x && x > b2.getPosition().x - b2.getLocalBounds().width)
                SetIndDbt(ind_dbt + 1);
            else if ((y-this->y - 40)/20 < (int)listeCartes.size())
                return listeCartes[(y - this->y - 40)/20];
        }
        else
        {
            if (y < b1.getPosition().y && y > b1.getPosition().y - b1.getLocalBounds().width
                && x > b1.getPosition().x && x < b1.getPosition().x + b1.getLocalBounds().height)
                SetIndDbt(ind_dbt - 1);
            else if (y > b2.getPosition().y && y < b2.getPosition().y + b2.getLocalBounds().width
                && x < b2.getPosition().x && x > b2.getPosition().x - b2.getLocalBounds().height)
                SetIndDbt(ind_dbt + 1);
            else if ( !isVertical && (x - this->x - 40)/height < (int)listeCartes.size() && (x - this->x - 40)/height >= 0)
                return listeCartes[(x - this->x - 40)/height];
        }
        
        return nullptr;
    }
    
    void Editeur::SetIndDbt(int value)
    {
        //std::cout<<"click"<<std::endl;   
        if (listeCartes.size() < nb_elem)
            ind_dbt = 0;
        else if (value < 0)
            ind_dbt = 0;
        else if (value > (int)(listeCartes.size() - nb_elem))
            ind_dbt = listeCartes.size() - nb_elem;
        else
            ind_dbt = value;
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
