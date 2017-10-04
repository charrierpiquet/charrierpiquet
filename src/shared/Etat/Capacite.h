// Generated by dia2code
#ifndef ETAT__CAPACITE__H
#define ETAT__CAPACITE__H

#include <string>

namespace Etat {
  class Objet;
}

#include "Objet.h"

namespace Etat {

  /// class Capacite - 
  class Capacite : public Etat::Objet {
    // Attributes
  private:
    std::string keyWord;
    int categorie;
    // Operations
  public:
    std::string GetKeyWord ();
    int GetCategorie ();
    Capacite (std::string motclef, int type, int id, int prop);
    // Setters and Getters
  };

};

#endif
