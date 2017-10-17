#include "RenduCarte.h"
#include <iostream>


namespace Render
{
	RenduCarte::RenduCarte(std::weak_ptr<Etat::Objet> carte, int posX, int posY)
	{
		sf::Texture texture;
		if(!texture.loadFromFile("..\\..\\..\\res\\cartes\\" + carte.getname() + ".png"))
		{
			return 1;
		}
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(posX,posY);
		sprite.setScale(sf::Vector2f(1.f,1.f));		
		sprite.setOrigin(sprite.getTexture().getWidth()/2,sprite.getTexture().getHeight()*sprite.getTexture().getWidth()/2);
		posX=posX;
		posY=posY;
		carte=carte;
	}
	
	int GetPosX() const
	{
		return posX;
	}
	
	int GetPosY() const
	{
		return posY;
	}
	
	bool GetIsSelected() const
	{
		return isSelected;
	}
	
	std::weak_ptr<Objet> GetCarte() const
	{
		return carte;
	}
	
	void Draw()
	{
		
		if isSelected==true
		{
			sprite.setColor(sf::Color(150,25,25));
		}
		
		if carte.isTap==true
		{
			sprite.setRotation(90);
		}
		
		window->draw(sprite);
	}
	
}
	
