// Generated by dia2code
#ifndef ENGINE__COMMAND__H
#define ENGINE__COMMAND__H


namespace Engine {

  /// class Command - 
  class Command {
    // Operations
  public:
    virtual void Execute (Etat::State& state) = 0;
    // Setters and Getters
  };

};

#endif