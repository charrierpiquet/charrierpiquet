#ifndef ETAT__STATE__H
#define ETAT__STATE__H

#include <vector>
#include <memory>

namespace Etat {
  class Joueur;
  class Objet;
  class Carte;
}

#include "Joueur.h"
#include "Objet.h"
#include "Carte.h"

namespace Etat {

  /// class State - 
  class State {
    // Associations
    // Attributes
  private:
    int joueur;
    int phase;
    std::vector<std::shared_ptr<Joueur> > joueurs;
    int priorite;
    std::vector<std::shared_ptr<Objet> > pile;
    std::vector<std::shared_ptr<Carte> > battlefield;
    int nbJoueur;
    // Operations
  public:
    State (int nb = 2);
    void IncrPriority ();
    void IncrPhase ();
    void AddCardPile (std::shared_ptr<Objet> card);
    void AddCardBattlefield (std::shared_ptr<Carte> card);
    std::vector<std::shared_ptr<Joueur> >  GetJoueurs() const;
    void DelCardBattlefield (int ind);
    void DelCardPile (int ind);
    std::vector<std::shared_ptr<Objet> >  GetPile () const;
    std::vector<std::shared_ptr<Carte> > GetBattlefield () const;
    int GetPhase () const;
    std::string GetPhaseName() const;
    int GetPriority() const;
    int GetJoueurTour() const;
    // Setters and Getters
  };

};

#endif
