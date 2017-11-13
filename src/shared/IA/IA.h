#ifndef IA_BASE_H
#define IA_BASE_H

#include <vector>
#include <memory>

namespace IA {

  /// class IA_base - 
  class IA_base {
    // Associations
    // Attributes
    std::shared_ptr<Etat::State> currentState;
    std::shared_ptr<Engine::Moteur> engine;
    // Operations
  public:
    IA (std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur);
    void think();
    // Setters and Getters
  };

};

#endif
