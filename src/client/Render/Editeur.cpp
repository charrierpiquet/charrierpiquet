#include "Editeur.h"
//#include "Etat/Objet.h"
//#include "Etat/Carte.h"
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
        {   
            b1.setRotation(270);
            b1.setScale(this->height/b1.getGlobalBounds().height,1);
            b1.setPosition(this->x+this->nom.getCharacterSize()*1.5 - b1.getGlobalBounds().width, this->y +b1.getGlobalBounds().height);
            
            //b1.setOrigin(b1.getGlobalBounds().width/2., b1.getGlobalBounds().height/2.);
            
            //b1.move(b1.getGlobalBounds().width/2.,b1.getGlobalBounds().height/2. );
            b2.setRotation(90);
            b2.setScale(this->height/b2.getGlobalBounds().height,1);
            b2.setPosition(this->x+this->width-b2.getGlobalBounds().width, this->y );
            
            //b2.setOrigin(b2.getGlobalBounds().width/2.,b2.getGlobalBounds().height/2.);
            
            //b2.move(b2.getGlobalBounds().width/2.,b2.getGlobalBounds().height/2. );
        }
        else
        {
            b1.setScale(this->width/b1.getGlobalBounds().width,1);
            b1.setPosition(this->x, this->y+20);
            
            //b1.setOrigin(b1.getGlobalBounds().left + b1.getGlobalBounds().width/2.,b1.getGlobalBounds().top + b1.getGlobalBounds().height/2.);
            //b1.move(b1.getGlobalBounds().width/2.,b1.getGlobalBounds().height/2. );
            
            b2.setRotation(180);
            b2.setScale(this->width/b2.getGlobalBounds().width,1);
            b2.setPosition(this->x + b2.getGlobalBounds().width, this->y+this->height);
            
            //b2.setOrigin(b2.getGlobalBounds().left + b2.getGlobalBounds().width/2.,b2.getGlobalBounds().top + b2.getGlobalBounds().height/2.);
            
            //b2.move(b2.getGlobalBounds().width/2.,b2.getGlobalBounds().height/2. );
        }        
    }
    
    void Editeur::Actu(const std::vector<std::shared_ptr<Etat::Objet> >& list_carte)
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
                    
                    if (!listeCartes[i]->GetIsCapacite())
                        tt.loadFromFile("res/cartes/" + listeCartes[i]->GetName() + ".png");        
                    else
                         tt.loadFromFile("res/capacite_default.jpg");
                    
                    texture.push_back(tt);

                        std::shared_ptr<sf::Sprite> sprite (new sf::Sprite());
                        
                        sprite->setTexture(texture[texture.size()-1]);                
                        sprite->setScale(height/sprite->getGlobalBounds().height,height/sprite->getGlobalBounds().height);
                        sprite->setPosition(b1.getGlobalBounds().left + b1.getGlobalBounds().width + height*(i-ind_dbt), y);
                        
                        //sprite->setOrigin(sprite->getGlobalBounds().width/2.,sprite->getGlobalBounds().height/2.);
                        
                        
                        if (!listeCartes[i]->GetIsCapacite())
                            if (std::static_pointer_cast<Etat::Carte>(listeCartes[i])->GetIsTap())
                            {
                                sprite->setRotation(90);
                                sprite->move(sprite->getGlobalBounds().width,height - sprite->getGlobalBounds().height);
                            }

                        //sprite->move(sprite->getGlobalBounds().width/2.,sprite->getGlobalBounds().height/2. );
                        spriteCarte.push_back(sprite);       
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
                    txt->setPosition(x,b1.getGlobalBounds().top + b1.getGlobalBounds().height+ txt->getCharacterSize()*(i - ind_dbt)*1.5);
                    spriteCarte.push_back(txt);
                }
        }         
    }    
    
    void Editeur::Draw(sf::RenderTarget& target)
    {
        std::string str = nom.getString();
        nom.setString(nom.getString() + " : " + std::to_string(listeCartes.size()));
        target.draw(b1);
        target.draw(b2);
        target.draw(nom);
        nom.setString(str);
        
        for(unsigned int i = 0 ; i < spriteCarte.size() ; i ++)
        {
            //std::cout<<i<<" "<<ind_dbt<<" "<<listeCartes.size()<<" "<<spriteCarte.size()<<std::endl;
            target.draw(*spriteCarte[i]);
            // c'est pas opti mais c'étais plus pratique de faire ça ici une fois le reste fait
            //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
            if(!listeCartes[i+ind_dbt]->GetIsCapacite())
            {
                Etat::Carte* carteTampon = (Etat::Carte*)listeCartes[i+ind_dbt].get();
                
                //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                if (carteTampon->GetCounter() != 0)
                    Bonus(std::to_string(carteTampon->GetCounter()),i,0,sf::Color::Blue,target);
                if (carteTampon->GetIsCreature())
                {
                    Etat::Creature* creatureTampon = (Etat::Creature*)listeCartes[i+ind_dbt].get();
                    //std::cout<<creatureTampon->GetBonusEOT()<<std::endl;
                    //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                    if (creatureTampon->GetBonusEOT() != 0)
                        Bonus(std::to_string(creatureTampon->GetBonusEOT()),i,20,sf::Color::Green,target);
                    //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                    if (creatureTampon->GetBlessure() > 0)
                        Bonus(std::to_string(creatureTampon->GetBlessure()),i,40,sf::Color::Red,target);
                    //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
                }   
            }
        }
    }
    
    void Editeur::Bonus(std::string str, int ind_sprite, int offset, sf::Color couleur, sf::RenderTarget& target)
    {
        //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
        sf::Text marqueurs;
        marqueurs.setCharacterSize(18);
        marqueurs.setFont(font);
        //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
        marqueurs.setString(str);
        //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
        marqueurs.setColor(couleur);
        marqueurs.setPosition(
            std::static_pointer_cast<sf::Sprite>(spriteCarte[ind_sprite])->getGlobalBounds().left+5 + offset,
            std::static_pointer_cast<sf::Sprite>(spriteCarte[ind_sprite])->getGlobalBounds().top +
            std::static_pointer_cast<sf::Sprite>(spriteCarte[ind_sprite])->getGlobalBounds().height/2 );
        //std::cout<<"jusqu'ici tout vas bien"<<std::endl;
        target.draw(marqueurs);
           
    }
    
    std::shared_ptr<Etat::Objet> Editeur::Click(int x, int y)
    {
        /*std::cout<< "x : "<< x ;
        std::cout<< "  y : "<< y ;
        std::cout<<std::endl;
        std::cout<< "  b1x : " << b1.getPosition().x ;
        std::cout<< "  b1y : " << b1.getPosition().y;
        std::cout<< "  b1w : " << b1.getGlobalBounds().width;
        std::cout<< "  b1h : " << b1.getGlobalBounds().height;
        std::cout<<std::endl;
        std::cout<< "  b2x : " << b2.getPosition().x ;
        std::cout<< "  b2y : " << b2.getPosition().y;
        std::cout<< "  b2w : " << b2.getGlobalBounds().width;
        std::cout<< "  b2h : " << b2.getGlobalBounds().height;
        std::cout<<std::endl;*/
        
        if (y > b1.getGlobalBounds().top && y < b1.getGlobalBounds().top + b1.getGlobalBounds().height
            && x > b1.getGlobalBounds().left && x < b1.getGlobalBounds().left + b1.getGlobalBounds().width)
            SetIndDbt(ind_dbt - 1);
        else if (y > b2.getGlobalBounds().top && y < b2.getGlobalBounds().top + b2.getGlobalBounds().height
            && x > b2.getGlobalBounds().left && x < b2.getGlobalBounds().left + b2.getGlobalBounds().width)
            SetIndDbt(ind_dbt + 1);
        
        else if (isVertical && (y - b1.getGlobalBounds().top - b1.getGlobalBounds().height)/18 < (int)listeCartes.size())
            return listeCartes[(y - b1.getGlobalBounds().top - b1.getGlobalBounds().height)/18 + ind_dbt];
        else if ( !isVertical && (x - b1.getGlobalBounds().left - b1.getGlobalBounds().width)/height < (int)listeCartes.size() )
            return listeCartes[(x - b1.getGlobalBounds().left - b1.getGlobalBounds().width)/height + ind_dbt];
        
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
