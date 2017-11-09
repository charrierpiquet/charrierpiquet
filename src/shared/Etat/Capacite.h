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
    Capacite (std::string motclef, int type, int id, int prop, std::string nom);
    std::string GetKeyWord () const;
    int GetCategorie () const;
    // Setters and Getters
  };

};

#endif
