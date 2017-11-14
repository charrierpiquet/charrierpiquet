#ifndef IA_BASE_H
#define IA_BASE_H

#include <vector>
#include <memory>

#include <Etat/State.h>
#include <Engine/Moteur.h>

namespace IA {

  /// class IA_base - 
  class IA_base {
    // Associations
    // Attributes
  private:
    std::shared_ptr<Etat::State> currentState;
    std::shared_ptr<Engine::Moteur> engine;
    // Operations
  public:
    IA_base (std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur);
    void Think();
    // Setters and Getters
  };

};

#endif
