#ifndef ENGINE__LOADCOMMAND__H
#define ENGINE__LOADCOMMAND__H

#include <string>

namespace Engine {
  class Command;
}

#include "Command.h"
#include "../Etat.h"

namespace Engine {

  /// class LoadCommand - 
  class LoadCommand : public Engine::Command {
    // Attributes
  private:
    std::string deck1;
    std::string deck2;
    // Operations
  public:
    LoadCommand (std::string Deck1,std::string Deck2);
    void Execute (std::shared_ptr<Etat::State> state);
    // Setters and Getters
  };

};

#endif
