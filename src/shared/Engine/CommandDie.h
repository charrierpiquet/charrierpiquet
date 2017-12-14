// Generated by dia2code
#ifndef ENGINE__COMMANDDIE__H
#define ENGINE__COMMANDDIE__H

#include <memory>
#include <json/json.h>

namespace Etat {
  class State;
};
namespace Engine {
  class CommandDie;
  class Command;
}

#include "Etat/State.h"
#include "Command.h"

namespace Engine {

  /// class CommandDie - 
  class CommandDie : public Engine::Command {
    // Associations
    // Attributes
  private:
    int id_carte;
    int id_prop;
    // Operations
  public:
    CommandDie (std::shared_ptr<Etat::Carte> carte);
    void Execute (std::shared_ptr<Etat::State> state);
    void Undo (std::shared_ptr<Etat::State> state);
    Json::Value Serialize () const;
    CommandDie* Deserialize (const Json::Value& in);
    CommandDie ();
    // Setters and Getters
  };

};

#endif
