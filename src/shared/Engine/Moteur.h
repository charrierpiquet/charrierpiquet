#ifndef ENGINE__MOTEUR__H
#define ENGINE__MOTEUR__H

#include <memory>
#include <map>

namespace Engine {
  class Command;
}

#include "Command.h"

namespace Engine {

  /// class Moteur - 
  class Moteur {
    // Associations
    // Attributes
  private:
    std::shared_ptr<Etat::State> currentState;
    std::vector<std::shared_ptr<Command> > commands;
    // Operations
  public:
    Moteur (std::shared_ptr<Etat::State> state);
    void AddCommand (std::shared_ptr<Command> cmd);
    void Update ();
    // Setters and Getters
  };

};

#endif
