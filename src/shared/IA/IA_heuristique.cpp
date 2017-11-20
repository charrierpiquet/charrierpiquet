#include "IA_heuristique.h"
#include "Engine/BlockCommand.h"
#include <iostream>
#include <ctime>
#include <Engine/CastCommand.h>
#include <Engine/LetPriorityCommand.h>
#include <Engine/AttackCommand.h>
#include <cstdlib>
#include <ctime>




namespace IA {

    IA_heuristique::IA_heuristique(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur)
    {
        currentState = state;
        engine = moteur;

    }

    void IA_heuristique::Think()
    {
        std::vector<int> list_val_cmd;
        std::vector<std::shared_ptr<Engine::Command> > list_cmd;
    }
    
    std::vector<std::shared_ptr<Engine::Command> > IA_heuristique::GetListCommand()
    {
       std::vector<std::shared_ptr<Engine::Command> > sortie;
       
       return sortie;
    }
    
    int IA_heuristique::EvalCmd(std::shared_ptr<Engine::Command> cmd)
    {
        return 0;
    }
    
    std::shared_ptr<Engine::Command> IA_heuristique::PhaseAttaque()
    {
        return std::shared_ptr<Engine::AttackCommand>(new Engine::AttackCommand());
    }
    
    std::shared_ptr<Engine::Command> IA_heuristique::PhaseBloqueur()
    {
        return std::shared_ptr<Engine::BlockCommand>(new Engine::BlockCommand());
    }

}


