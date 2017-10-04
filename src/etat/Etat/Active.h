// Generated by dia2code
#ifndef ETAT__ACTIVE__H
#define ETAT__ACTIVE__H


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
    Cout GetCost ();
    Active (Cout cout, std::string motclef);
    // Setters and Getters
  };

};

#endif
