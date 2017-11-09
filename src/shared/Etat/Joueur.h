#ifndef ETAT__JOUEUR__H
#define ETAT__JOUEUR__H

#include <memory>
#include <vector>

namespace Etat {
  class ManaPool;
  class Carte;
  class Objet;
}

#include "ManaPool.h"
#include "Carte.h"
#include "Objet.h"

namespace Etat {

  /// class Joueur - 
  class Joueur {
    // Associations
    // Attributes
  private:
    std::shared_ptr<ManaPool> manaPool;
    int pv;
    bool aJoueTerrain;
    std::vector<std::shared_ptr<Carte> > hand;
    std::vector<std::shared_ptr<Carte> > graveyard;
    std::vector<std::shared_ptr<Carte> > library;
    // Operations
  public:
    Joueur ();
    int GetPv () const;
    void SetPv (int Pv);
    void Draw ();
    void Discard ();
    std::vector<std::shared_ptr<Carte> > GetHand () const;
    bool GetAJoueTerrain () const;
    void SetAJoueTerrain (bool value);
    std::vector<std::shared_ptr<Carte> > GetLibrary () const;
    std::vector<std::shared_ptr<Carte> > GetGraveyard () const;
    std::shared_ptr<ManaPool> GetManaPool () const;
    void AddCardLibrary (std::shared_ptr<Carte> card);
    void AddCardHand (std::shared_ptr<Carte> card);
    void AddCardGraveyard (std::shared_ptr<Carte> card);
    void DelCardHand (int ind);
    void DelCardLibrary (int ind);
    void DelCardGraveyard (int ind);
    // Setters and Getters
  };

};

#endif
