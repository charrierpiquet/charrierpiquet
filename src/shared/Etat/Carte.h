// Generated by dia2code
#ifndef ETAT__CARTE__H
#define ETAT__CARTE__H

#include <vector>
#include <memory>
#include <string>

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
    int counters;
    std::vector<std::shared_ptr<Capacite> > ability;
    // Operations
  public:
    Carte (bool permanent, bool land, bool creature, bool token, std::string nom, std::shared_ptr<Cout> cout, std::vector<std::shared_ptr<Capacite> > capa, int id, int prop);
    int GetCounter () const;
    bool GetIsLand () const;
    bool GetIsPermanent () const;
    bool GetIsCreature () const;
    bool GetIsToken () const;
    bool GetIsTap () const;
    std::vector<std::shared_ptr<Capacite> > GetAbility () const;
    void SetIsTap (bool value);
    void SetCounter (int value);
    // Setters and Getters
  };

};

#endif
