// Generated by dia2code
#ifndef RENDER__RENDUCARTE__H
#define RENDER__RENDUCARTE__H

#include <memory>
#include <SFML/Graphics.hpp>

//namespace Etat
//{
	//class Carte;
//}

//#include "Carte.h"

namespace Render {

  /// class RenduCarte - 
  class RenduCarte {
    // Attributes
  private:
    std::weak_ptr<Etat::Objet> carte;
    bool isSelected;
    int posX;
    int posY;
    sf::Sprite sprite;
    // Operations
  public:
    RenduCarte ();
    void Draw (sf::RenderTarget& target);
    std::weak_ptr<Objet> GetCarte () const;
    bool GetIsSelected () const;
    int GetPosX () const;
    int GetPosY () const;
    // Setters and Getters
  };
  
  

};

#endif
