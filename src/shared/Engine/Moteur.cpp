#include "Moteur.h"
#include <iostream>

namespace Engine
{
    Moteur::Moteur(std::shared_ptr<Etat::State> state)
    {
        currentState = state;
    }

    void Moteur::AddCommand(Command* cmd)
    {
        //if (commands.find(priority) == commands.end())
        //    commands[priority] = std::unique_ptr<Command>(cmd);
        //else
        //    std::cout<<"erreur : impossible d'ajouter cette commande."<<std::endl<<"\tniveau de priorite deja utilise."<<std::endl;
        commands.push_back(std::unique_ptr<Command>(cmd));
    }
    
    void Moteur::Update()
    {
        //std::map<int, std::unique_ptr<Command>::iterator it = commands.begin();
        //while (it != commands.end())
        //{
        //    std::static_pointer_cast<Command>(it->second)->Execute(currentState);
        //    it++;
        //}
        for (int i = 0 ; i < (int)commands.size() ; i++ )
            commands[i]->Execute(*currentState);
    }
    
}
