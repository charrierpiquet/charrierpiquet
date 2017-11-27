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
    std::vector<std::shared_ptr<Engine::CastCommand> > GetListCommand(); // eventuellement mettre un std::shared_ptr<Etat::State> en param pour plus tard...
    int EvalCmd(std::shared_ptr<Engine::Command> cmd);
    std::shared_ptr<Engine::Command> PhaseAttaque();
    std::shared_ptr<Engine::Command> PhaseBloqueur();
    
    // Setters and Getters
  };

};

#endif

