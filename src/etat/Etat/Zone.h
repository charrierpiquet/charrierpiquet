// Generated by dia2code
#ifndef ETAT__ZONE__H
#define ETAT__ZONE__H


namespace Etat {
  class Joueur;
  class Objet;
}

#include "Joueur.h"
#include "Objet.h"

namespace Etat {

  /// class Zone - 
  class Zone {
    // Attributes
  private:
    Joueur proprietaire;
    int visibilite;
    string name;
    // Operations
  public:
    int GetVisibilite ();
    Joueur GetProprietaire ();
    string GetName ();
    Zone (Joueur prop, int visi, string nom);
    ~Zone ();
    // Setters and Getters
  };

};

#endif
