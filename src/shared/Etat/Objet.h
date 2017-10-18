// Generated by dia2code
#ifndef ETAT__OBJET__H
#define ETAT__OBJET__H

#include <memory>

namespace Etat {
  class Objet;
}


namespace Etat {

  /// class Objet - 
  class Objet {
    // Attributes
  private:
    bool isCapacite;
    std::weak_ptr<Objet> target;
    int indJoueur;
    int idObj;
    std::string oracle;
    // Operations
  public:
    Objet (bool capa, int id, int prop);
    void SetTarget (std::weak_ptr<Objet> cible);
    std::weak_ptr<Objet> GetTarget () const;
    bool GetIsCapacite () const;
    int GetIndJoueur () const;
    int GetIdObj () const;
    void SetOracle(std::string txt);
    std::string GetOracle() const;
    // Setters and Getters
  };

};

#endif
