#ifndef ETAT__MANAPOOL__H
#define ETAT__MANAPOOL__H


namespace Etat {
  class Cout;
}

#include "Cout.h"

namespace Etat {

  /// class ManaPool - 
  class ManaPool {
    // Attributes
  private:
    int inc;
    int black;
    int blue;
    int green;
    int multi;
    // Operations
  public:
    void AddInc ();
    void AddBlue ();
    void AddBlack ();
    void AddGreen ();
    void AddMulti ();
    void Vider ();
    bool Payer (Cout cost);
    int GetInc () const;
    int GetBlue () const;
    int GetBlack () const;
    int GetGreen () const;
    int GetMulti () const;
    // Setters and Getters
  };

};

#endif
