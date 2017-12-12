#include "TestRecord.h"
#include "Ai.h"
#include "Engine.h"
#include "Etat.h"

namespace Test
{
    void TestRecord()
    {
        std::vector<std::string> Decks;
        Decks.push_back("Deck1");Decks.push_back("Deck2");
        std::shared_ptr<Etat::State> state (new Etat::State(Decks));
        std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(state));
        moteur->SetRecord(true);
        Ai::Ia_Base ia (state, moteur);
        
    
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));     
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(0)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(1)));
        moteur->Update();
        
        bool end = true;
        while (end)
        {
            ia.Think();            
            moteur->Update();
            
            if(state->GetJoueurs()[0]->GetPv() == 0 || state->GetJoueurs()[1]->GetPv() == 0)
                end = false;
        }
        
    }
    
}