// Generated by dia2code
#ifndef ENGINE__COMMANDBLOCK__H
#define ENGINE__COMMANDBLOCK__H

#include <memory>
#include <json/json.h>

namespace Etat {
  class State;
};
namespace Engine {
  class CommandBlock;
  class Command;
}

#include "Etat/State.h"
#include "Command.h"

namespace Engine {

  /// class CommandBlock - 
  class CommandBlock : public Engine::Command {
    // Associations
    // Attributes
  private:
    int idBloqueur;
    int idBloque;
    // Operations
  public:
    CommandBlock (std::shared_ptr<Etat::Creature> bloqueur, std::shared_ptr<Etat::Creature> bloque);
    void Execute (std::shared_ptr<Etat::State> state);
    void Undo (std::shared_ptr<Etat::State> state);
    /// 			
    Json::Value Serialize () const;
    CommandBlock* Deserialize (const Json::Value& in);
    CommandBlock ();
    // Setters and Getters
  };

};

#endif
