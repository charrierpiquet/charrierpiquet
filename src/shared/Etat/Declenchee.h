#ifndef ETAT__DECLENCHEE__H
#define ETAT__DECLENCHEE__H

#include <string>

namespace Etat {
  class Capacite;
}

#include "Capacite.h"

namespace Etat {

  /// class Declenchee - 
  class Declenchee : public Etat::Capacite {
    // Attributes
  private:
    int event;
    // Operations
  public:
    Declenchee (int evnt, std::string motclef, int id, int prop, std::string nom);
    int GetEvent ();
    // Setters and Getters
  };

};

#endif
