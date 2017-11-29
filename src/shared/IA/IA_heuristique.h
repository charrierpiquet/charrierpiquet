#ifndef IA_HEURISTIQUE_H
#define IA_HEURISTIQUE_H

#include <vector>
#include <memory>

#include <Etat/State.h>
#include <Engine/Moteur.h>
#include <Engine/CastCommand.h>
#include <Engine/Command.h>

namespace IA {

  /// class IA_base - 
  class IA_heuristique {
    // Associations
    // Attributes
  private:
    std::shared_ptr<Etat::State> currentState;
    std::shared_ptr<Engine::Moteur> engine;
    // Operations
  public:
    IA_heuristique (std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur);
    void Think();
    int EvalCmd(std::shared_ptr<Engine::CastCommand> cmd);
    std::vector<std::shared_ptr<Engine::CastCommand> > GetListCommand();
    std::shared_ptr<Engine::Command> PhaseAttaque();
    std::shared_ptr<Engine::Command> PhaseBloqueur();
    void Penser();  
    // Setters and Getters
  };

};

#endif

