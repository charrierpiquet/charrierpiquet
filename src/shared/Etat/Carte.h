// Generated by dia2code
#ifndef ETAT__CARTE__H
#define ETAT__CARTE__H

#include <string>
#include <vector>

namespace Etat {
  class Cout;
  class Capacite;
  class Objet;
}

#include "Cout.h"
#include "Capacite.h"
#include "Objet.h"

namespace Etat {

  /// class Carte - 
  class Carte : public Etat::Objet {
    // Associations
    // Attributes
  private:
    bool isPermanent;
    bool isLand;
    bool isTap;
    bool isCreature;
    bool isToken;
    std::string name;
    Cout cost;
    int counters;
    std::vector<Capacite> ability;
    // Operations
  public:
    std::string GetName ();
    Cout GetCost ();
    int GetCounter ();
    bool GetIsLand ();
    bool GetIsPermanent ();
    bool GetIsCreature ();
    bool GetIsToken ();
    bool GetIsTap ();
    std::vector<Capacite> GetAbility ();
    void SetIsTap (bool value);
    void SetCounter (int value);
    Carte (bool permanent, bool land, bool creature, bool token, std::string nom, Cout cout, std::vector<Capacite> capa, int id, int prop);
    // Setters and Getters
  };

};

#endif
