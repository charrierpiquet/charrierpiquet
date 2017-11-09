#ifndef ENGINE__ATTACKCOMMAND__H
#define ENGINE__ATTACKCOMMAND__H

#include <vector>
#include <memory>

namespace Engine {
  class Command;
}

#include "Command.h"
#include "Etat/State.h"
#include "Etat/Creature.h"

namespace Engine {

  /// class AttackCommand - 
  class AttackCommand : public Engine::Command {
    // Attributes
  private:
    std::vector<std::shared_ptr<Etat::Creature> > attaquant;
    // Operations
  public:
    //AttackCommand ();
    void SupprAttaquant (std::shared_ptr<Etat::Creature> crea);
    void AddAttaquant (std::shared_ptr<Etat::Creature> crea);
    void Execute (std::shared_ptr<Etat::State> state);
    // Setters and Getters
  };

};

#endif
