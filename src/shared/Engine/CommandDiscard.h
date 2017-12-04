// Generated by dia2code
#ifndef ENGINE__COMMANDDISCARD__H
#define ENGINE__COMMANDDISCARD__H

#include <memory>

namespace Etat {
  class State;
};
namespace Engine {
  class Command;
}

#include "Etat/State.h"
#include "Command.h"

namespace Engine {

  /// class CommandDiscard - 
  class CommandDiscard : public Engine::Command {
    // Associations
    // Attributes
  public:
    int idProp;
  private:
    int iDJoueur;
    // Operations
  public:
    CommandDiscard (int joueur);
    void Execute (std::shared_ptr<Etat::State> state);
    void Undo (std::shared_ptr<Etat::State> state);
    // Setters and Getters
  };

};

#endif