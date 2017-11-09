#ifndef ENGINE__BLOCKCOMMAND__H
#define ENGINE__BLOCKCOMMAND__H

#include <vector>
#include <memory>

namespace Engine {
  class Command;
}

#include "Command.h"
#include "Etat/State.h"
#include "Etat/Creature.h"

namespace Engine {

  /// class BlockCommand - 
  class BlockCommand : public Engine::Command {
    // Attributes
  private:
    std::vector<std::shared_ptr<Etat::Creature> > attaquant;
    std::vector<std::shared_ptr<Etat::Creature> > bloque;
    std::vector<std::shared_ptr<Etat::Creature> > bloqueur;
    // Operations
  public:
    BlockCommand (std::vector<std::shared_ptr<Etat::Creature> > attaq);
    void SupprBloqueur (std::shared_ptr<Etat::Creature> crea);
    void AddBloqueur (std::shared_ptr<Etat::Creature> bloqueur, std::shared_ptr<Etat::Creature> bloque);
    void Execute (std::shared_ptr<Etat::State> state);
    // Setters and Getters
  };

};

#endif
