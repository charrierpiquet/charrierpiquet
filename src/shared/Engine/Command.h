#ifndef ENGINE__COMMAND__H
#define ENGINE__COMMAND__H

#include "Etat/State.h"

namespace Engine {

  /// class Command - 
  class Command {
    // Operations
  public:
    Command (void) { } ;
    ~Command (void) { };
    virtual void Execute (std::shared_ptr<Etat::State> state) = 0;
    // Setters and Getters
  };

};

#endif
