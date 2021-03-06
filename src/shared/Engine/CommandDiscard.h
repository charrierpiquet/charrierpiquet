// Generated by dia2code
#ifndef ENGINE__COMMANDDISCARD__H
#define ENGINE__COMMANDDISCARD__H

#include <memory>
#include <json/json.h>

namespace Etat {
  class State;
};
namespace Engine {
  class CommandDiscard;
  class Command;
}

#include "Etat/State.h"
#include "Command.h"

namespace Engine {

  /// class CommandDiscard - 
  class CommandDiscard : public Engine::Command {
    // Associations
    // Attributes
  private:
    int idJoueur;
    bool empty;
    int alea;
    // Operations
  public:
    CommandDiscard (int joueur);
    void Execute (std::shared_ptr<Etat::State> state);
    void Undo (std::shared_ptr<Etat::State> state);
    Json::Value Serialize () const;
    CommandDiscard* Deserialize (const Json::Value& in);
    CommandDiscard ();
    // Setters and Getters
  };

};

#endif
