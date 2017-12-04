// Generated by dia2code
#ifndef ETAT__STATE__H
#define ETAT__STATE__H

#include <vector>
#include <memory>
#include <string>

namespace Etat {
  class Objet;
  class Carte;
  class Creature;
  class Joueur;
}

#include "Objet.h"
#include "Carte.h"
#include "Creature.h"
#include "Joueur.h"

namespace Etat {

  /// class State - 
  class State {
    // Associations
    // Attributes
  private:
    int joueur;
    int phase;
    int priorite;
    std::vector<std::shared_ptr<Joueur> > joueurs;
    std::vector<std::shared_ptr<Objet> > pile;
    std::vector<std::shared_ptr<Carte> > battlefield;
    std::vector<std::shared_ptr<Creature> > list_attaquant;
    std::vector<std::shared_ptr<Creature> > list_bloqueur;
    std::vector<std::shared_ptr<Creature> > list_bloque;
    int id;
    // Operations
  public:
    State (std::vector<std::string> list_deck);
    void SetPriority (int value);
    void SetPhase (int value);
    void AddCardPile (std::shared_ptr<Objet> card);
    void AddCardBattlefield (std::shared_ptr<Carte> card);
    std::vector<std::shared_ptr<Joueur> > GetJoueurs () const;
    void DelCardBattlefield (int ind);
    void DelCardPile (int ind);
    std::vector<std::shared_ptr<Objet> > GetPile () const;
    std::vector<std::shared_ptr<Carte> > GetBattlefield () const;
    int GetPhase () const;
    std::string GetPhaseName () const;
    int GetPriority () const;
    int GetJoueurTour () const;
    void AddListAttaquant (std::shared_ptr<Creature> crea);
    std::vector<std::shared_ptr<Creature> > GetAttaquants () const;
    void AddListBloqueur (std::shared_ptr<Creature> crea);
    std::vector<std::shared_ptr<Creature> > GetBloqueur () const;
    void AddListBloque (std::shared_ptr<Creature> crea);
    std::vector<std::shared_ptr<Creature> > GetListBloque () const;
    int GetInd ();
    void SetTour (int value);
    void ClearAtt();
    // Setters and Getters
  };

};

#endif
