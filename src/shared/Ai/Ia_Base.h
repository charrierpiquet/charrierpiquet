// Generated by dia2code
#ifndef AI__IA_BASE__H
#define AI__IA_BASE__H

#include <memory>

namespace Etat {
  class State;
};
namespace Engine {
  class Moteur;
}

#include "Etat/State.h"
#include "Engine/Moteur.h"

namespace Ai {

  /// class Ia_Base - 
  class Ia_Base {
    // Associations
    // Attributes
  protected:
    std::shared_ptr<Etat::State> currentState;
    std::shared_ptr<Engine::Moteur> engine;
    // Operations
  public:
    Ia_Base (std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur);
    void Think ();
    bool TryCast (std::shared_ptr<Etat::Cout> cost);
    // Setters and Getters
    const std::shared_ptr<Etat::State>& getCurrentState() const;
    void setCurrentState(const std::shared_ptr<Etat::State>& currentState);
    const std::shared_ptr<Engine::Moteur>& getEngine() const;
    void setEngine(const std::shared_ptr<Engine::Moteur>& engine);
  };

};

#endif
