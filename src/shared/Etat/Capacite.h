// Generated by dia2code
#ifndef ETAT__CAPACITE__H
#define ETAT__CAPACITE__H

#include <string>
#include <memory>

namespace Etat {
  class Carte;
  class Cout;
  class Objet;
}

#include "Carte.h"
#include "Cout.h"
#include "Objet.h"

namespace Etat {

  /// class Capacite - 
  class Capacite : public Etat::Objet {
    // Attributes
  private:
    std::string keyWord;
    bool needTarget;
    std::weak_ptr<Carte> source;
    // Operations
  public:
    Capacite (std::shared_ptr<Cout> cout, std::string motclef, int id, int prop, std::string nom, bool target, std::weak_ptr<Carte> source);
    std::string GetKeyWord () const;
    bool GetNeedTarget () const;
    std::weak_ptr<Carte> GetSource () const;
    void SetSource (std::weak_ptr<Carte> source);
    // Setters and Getters
  };

};

#endif
