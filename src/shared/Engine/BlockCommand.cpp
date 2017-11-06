#include "BlockCommand.h"

namespace Engine
{
    BlockCommand::BlockCommand (std::vector<std::shared_ptr<Etat::Creature> > attaq)
    {
        attaquant = attaq;
    }
    void BlockCommand::SupprBloqueur (std::shared_ptr<Etat::Creature> crea)
    {
        int ind=-1;
        for ( int i = 0 ; i < bloqueur.size() ; i++ )
            if ( crea == bloqueur[i] )
                ind = i;
        if (ind != -1)
        {
            bloqueur.erase(bloqueur.begin()+ind);
            bloque.erase(bloque.begin()+ind);
        }
            
    }
    void BlockCommand::AddBloqueur (std::shared_ptr<Etat::Creature> crea_bloqueur, std::shared_ptr<Etat::Creature> crea_bloque)
    {
        bloqueur.push_back(crea_bloqueur);
        bloque.push_back(crea_bloque);
    }
    void BlockCommand::Execute (Etat::State& state)
    {
        // les creatures bloqueuse inflige leur blessure aux creatures bloques
        
        // les creatures bloques infliges leurs blessures aux creature bloqueuses
        // dans l'ordre des creatures qui bloque et si ça depasse aux creatures suivantes
        
        // les creatures non bloques inflige leur force aux joueurs
        
    }
}