#include "Etat.h"
#include "Ai.h"
#include "Engine.h"
//#include "Test/TestRecord.h"
#include <iostream>

using namespace std;
using namespace Etat;

void TestRecord(void);

int main(int argc, char* argv[]) {
    //Exemple exemple;
    //exemple.setX(53);
    if (argc == 1)
        cout << "It works !" << endl;
    else if (argc == 2) {
        if ((string) argv[1] == "record")
            TestRecord();

    } else
        cout << "trop d'arguments" << endl;


    return 0;
}

void TestRecord() {
    std::vector<std::string> Decks;
    Decks.push_back("Deck1");
    Decks.push_back("Deck2");
    std::shared_ptr<Etat::State> state(new Etat::State(Decks));
    std::shared_ptr<Engine::Moteur> moteur(new Engine::Moteur(state));
    moteur->SetRecord(true);
    Ai::Ia_Base ia(state, moteur);


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
    while (end) {
        ia.Think();
        moteur->Update();

        if (state->GetJoueurs()[0]->GetPv() == 0 || state->GetJoueurs()[1]->GetPv() == 0)
            end = false;
    }

}
