#include "CastCommand.h"

namespace Engine
{
    CastCommand::CastCommand(std::shared_ptr<Etat::Objet> o, std::shared_ptr<Etat::Carte> s, std::shared_ptr<Etat::Objet> t)
    {
        obj = o;
        src = s;
        target = t;
    }
    
    void CastCommand::Execute(Etat::State& state)
    {
        // si payer les couts.
            // si src != null && objet est une capacite
                // si src est degager
                    // engager src
                    // creer une capacite sur la pile
            // sinon 
                // si obj est une carte et objet est dans la main placer objet sur la pile
        // afficher un message d'erreur
        
    }
    
}