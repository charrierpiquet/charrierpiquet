// Generated by dia2code
#ifndef ENGINE__COMMANDSOLVECOMBAT__H
#define ENGINE__COMMANDSOLVECOMBAT__H

#include <vector>
#include <memory>
#include <json/json.h>

namespace Etat {
  class State;
};
namespace Engine {
  class CommandSolveCombat;
  class Command;
}

#include "Etat/State.h"
#include "Command.h"

namespace Engine {

  /// class CommandSolveCombat - vide les liste d'attaquants et de bloqueurs et inflige les degats
  class CommandSolveCombat : public Engine::Command {
    // Associations
    // Attributes
  private:
    std::vector<int> idAttaquants;
    std::vector<int> idBloqueur;
    std::vector<int> idBloque;
    // Operations
  public:
    void Execute (std::shared_ptr<Etat::State> state);
    void Undo (std::shared_ptr<Etat::State> state);
    Json::Value Serialize () const;
    CommandSolveCombat* Deserialize (const Json::Value& in);
    // Setters and Getters
  };

};

#endif
