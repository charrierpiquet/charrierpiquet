#ifndef ETAT__CREATURE__H
#define ETAT__CREATURE__H

#include <string>
#include <vector>

namespace Etat {
  class Cout;
  class Capacite;
  class Carte;
}

#include "Cout.h"
#include "Capacite.h"
#include "Carte.h"

namespace Etat {

  /// class Creature - 
  class Creature : public Etat::Carte {
    // Attributes
  private:
    int force;
    int endurance;
    int bonusEOT;
    int blessure;
    bool malInvoc;
    // Operations
  public:
    Creature (int strengh, int thougness, bool token, std::string nom, Cout cout, std::vector<std::shared_ptr<Capacite> > capa, int id, int prop);
    int GetForce () ;
    int GetEndurance () ;
    bool GetMalInvoc () ;
    int GetBonusEOT () ;
    int GetBlessure () ;
    void SetBonusEOT (int value);
    void SetBlessure (int value);
    void SetMalInvoc (bool value);
    // Setters and Getters
  };

};

#endif
