// Generated by dia2code
#ifndef ENGINE__COMMAND__H
#define ENGINE__COMMAND__H

#include <memory>

namespace Etat {
  class State;
}

#include "Etat/State.h"

namespace Engine {

  /// class Command - 
  class Command {
    // Associations
    // Operations
  public:
    virtual void Execute (std::shared_ptr<Etat::State> state) = 0;
    virtual void Undo ( std::shared_ptr<Etat::State>) = 0;
    // Setters and Getters
  };

};

#endif
