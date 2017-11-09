#ifndef ENGINE__CASTCOMMAND__H
#define ENGINE__CASTCOMMAND__H

#include <memory>

namespace Engine {
  class Command;
}

#include "Command.h"

namespace Engine {

  /// class CastCommand - 
  class CastCommand : public Engine::Command {
    // Attributes
  private:
    std::shared_ptr<Etat::Objet> obj;
    std::shared_ptr<Etat::Carte> src;
    std::shared_ptr<Etat::Objet> target;
    // Operations
  public:
    CastCommand (std::shared_ptr<Etat::Objet> o, std::shared_ptr<Etat::Carte> s, std::shared_ptr<Etat::Objet> t);
    void Execute (std::shared_ptr<Etat::State> state);
    // Setters and Getters
  };

};

#endif
