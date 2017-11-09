#ifndef ETAT__ACTIVE__H
#define ETAT__ACTIVE__H

#include <string>

namespace Etat {
  class Cout;
  class Capacite;
}

#include "Cout.h"
#include "Capacite.h"

namespace Etat {

  /// class Active - 
  class Active : public Etat::Capacite {
    // Associations
    // Attributes
  private:
    Cout cost;
    // Operations
  public:
    Active (Cout cout, std::string motclef, int id, int prop, std::string nom);
    Cout GetCost () const;
    // Setters and Getters
  };

};

#endif
