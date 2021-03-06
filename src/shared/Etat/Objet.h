// Generated by dia2code
#ifndef ETAT__OBJET__H
#define ETAT__OBJET__H

#include <memory>
#include <string>

namespace Etat {
  class Objet;
  class Cout;
}

#include "Cout.h"

namespace Etat {

  /// class Objet - 
  class Objet {
    // Associations
    // Attributes
  private:
    bool isCapacite;
    std::weak_ptr<Objet> target;
    int indJoueur;
    int idObj;
    std::string oracle;
    std::string name;
    std::shared_ptr<Cout> cost;
    // Operations
  public:
    Objet (bool capa, int id, int prop, std::string nom, std::shared_ptr<Cout> cout);
    void SetTarget (std::weak_ptr<Objet> cible);
    std::weak_ptr<Objet> GetTarget () const;
    bool GetIsCapacite () const;
    int GetIndJoueur () const;
    int GetIdObj () const;
    void SetOracle (std::string txt);
    std::string GetOracle () const;
    std::string GetName () const;
    std::shared_ptr<Cout> GetCost ();
    // Setters and Getters
  };

};

#endif
