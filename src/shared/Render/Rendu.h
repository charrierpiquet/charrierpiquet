// Generated by dia2code
#ifndef RENDER__RENDU__H
#define RENDER__RENDU__H

#include <memory>

namespace Render {
  class Editeur;
}

#include "Editeur.h"

namespace Render {

  /// class Rendu - 
  class Rendu {
    // Associations
    // Attributes
  private:
    int dimensionX;
    int dimensionY;
    Editeur cimetiere1;
    Editeur cimetiere2;
    Editeur bf11;
    Editeur bf12;
    Editeur stack;
    Editeur bf21;
    Editeur bf22;
    Editeur listCapa;
    std::weak_ptr<Etat::State> state;
    // Operations
  public:
    Rendu (std::weak_ptr<State> etat);
    void Click (int x, int y);
    void Draw (sf::RenderTarget&  target);
    void Actu ();
    Editeur GetGrv1 () const;
    Editeur GetGrv2 () const;
    Editeur GetBf11 () const;
    Editeur GetBf12 () const;
    Editeur GetStack () const;
    Editeur GetBf21 () const;
    Editeur GetBf22 () const;
    int GetDimX () const;
    int GetDimY () const;
    // Setters and Getters
  };

};

#endif
