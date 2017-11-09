#ifndef ENGINE__LETPRIORITYCOMMAND__H
#define ENGINE__LETPRIORITYCOMMAND__H


namespace Engine {
  class Command;
}

#include "Command.h"

namespace Engine {

  /// class LetPriorityCommand - 
  class LetPriorityCommand : public Engine::Command {
    // Operations
  public:
    void Execute (std::shared_ptr<Etat::State> state);
    void Resolve(std::string keyword, std::shared_ptr<Etat::State>);
    // Setters and Getters
  };

};

#endif
