#ifndef RENDER__RENDU__H
#define RENDER__RENDU__H

#include <memory>

namespace Render {
  class Editeur;
}

#include "Etat/Objet.h"
#include "Etat/State.h"
#include "Editeur.h"


namespace Render {

  /// class Rendu - 
  class Rendu {
    // Associations
    // Attributes
  private:
    int dimensionX;
    int dimensionY;
    int joueur;
    
    Editeur cimetiere2;
    Editeur cimetiere1;
    Editeur bf21;
    Editeur bf22;
    Editeur stack;
    Editeur bf12;
    Editeur bf11;
    Editeur hand;
    Editeur listCapa;
    
    std::shared_ptr<Etat::State> state;
    std::shared_ptr<Etat::Objet> selectedCard;
    
    sf::Sprite sprite;
    
    sf::Text txt_etat;
    sf::Text txt_nomSelect;
    sf::Text txt_Oracle;
    sf::Text txt_instruction;
    
    sf::Texture texture;
    sf::Font font;
    
    sf::Texture ttMp;
    sf::Sprite mp;
    sf::Text nb;
    // Operations
  public:
    Rendu (std::shared_ptr<Etat::State> etat, int x, int y, int j);
    void Click (int x, int y);
    void Draw (sf::RenderTarget&  target);
    void DrawSelectedCard(sf::RenderTarget& target);
    void DrawManaPool(sf::RenderTarget& target, int i);
    void DrawBf(sf::RenderTarget& target, int joueur, Render::Editeur& bf1, Render::Editeur& bf2);
    //void Actu ();
    template<typename T> std::vector<std::shared_ptr<Etat::Objet> > Conv(std::vector<std::shared_ptr<T> > data);
    // Setters and Getters
  };

};

#endif
