#ifndef RENDER__EDITEUR__H
#define RENDER__EDITEUR__H

#include <string>
#include <vector>
#include <memory>

#include "Etat.h"
#include <SFML/Graphics.hpp>


namespace Render {

  /// class Editeur - 
  class Editeur {
    // Associations
    // Attributes
  private:
    int x;
    int y;
    int width;
    int height;
    unsigned int ind_dbt;
    unsigned int nb_elem;
    bool isVertical;
    sf::Text nom;
    std::vector<std::shared_ptr<Etat::Objet> >  listeCartes;
    std::vector<sf::Texture> texture;
    std::vector<std::shared_ptr<sf::Drawable> > spriteCarte;
    sf::Sprite b1;
    sf::Sprite b2;
    sf::Font font;
    sf::Texture textureB;
    // Operations
  public:
    Editeur (std::string nom, bool orientation, int x, int y, int width, int height);
    std::shared_ptr<Etat::Objet> Click (int x, int y);
    void Draw (sf::RenderTarget& target);
    void Actu (const std::vector<std::shared_ptr<Etat::Objet> >&  list_carte);
    int GetX () const;
    int GetY () const;
    int GetWidth () const;
    int GetHeight () const;
    int GetIndDbt () const;
    int GetNbElem () const;
    bool GetIsVertical () const;
    std::vector<std::shared_ptr<Etat::Objet> > GetCartes () const;
    void SetIndDbt (int value);
    void Bonus(std::string str,int ind_sprite,int offset, sf::Color couleur, sf::RenderTarget& target);
    // Setters and Getters
  };

};

#endif
