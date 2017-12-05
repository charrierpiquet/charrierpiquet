#include "CommandResolveCapa.h"
#include "Moteur.h"
#include "CommandDiscard.h"
#include "CommandDraw.h"

namespace Engine {

    CommandResolveCapa::CommandResolveCapa(std::shared_ptr<Etat::Capacite> capa, std::weak_ptr<Moteur> m) {
        engine = m;
        obj = capa;
        if (capa->GetNeedTarget())
            target = capa->GetTarget().lock();
        else
            target = nullptr;
    }

    void CommandResolveCapa::Execute(std::shared_ptr<Etat::State> state) {
        std::vector<std::shared_ptr<Etat::Capacite> > capaVide;
        std::shared_ptr<Etat::Cout> coutVide(new Etat::Cout(0,0,0,0,0));
        //std::cout<<obj->GetKeyWord()<<" "<<obj->GetKeyWord().compare("blue")<<" "<<obj->GetKeyWord().compare("green")<<std::endl;
        if (obj->GetKeyWord().compare("multi") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetMulti(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetMulti() + 1);
        else if (obj->GetKeyWord().compare("blue") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetBlue(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetBlue() + 1);
        else if (obj->GetKeyWord().compare("green") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetGreen(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetGreen() + 1);
        else if (obj->GetKeyWord().compare("black") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetBlack(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetBlack() + 1);
        else if (obj->GetKeyWord().compare("inc") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetInc(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetInc() + 1);
        else if (obj->GetKeyWord().compare("burn") == 0)
            state->GetJoueurs()[1 - obj->GetIndJoueur()]->SetPv(state->GetJoueurs()[1 - obj->GetIndJoueur()]->GetPv() - 1);
        else if (obj->GetKeyWord().compare("draw") == 0)
            engine.lock()->AddCommand(std::shared_ptr<CommandDraw>(new CommandDraw(obj->GetIndJoueur())));
        else if (obj->GetKeyWord().compare("TokenRat") == 0) {
            std::shared_ptr<Etat::Creature> Rat(new Etat::Creature(1, 1, true, (std::string)"Rat", coutVide, capaVide, state->GetInd(), obj->GetIndJoueur()));
            Rat->SetOracle("Creature Jeton 1/1\nJeton de creature rat,\ncree par Chef des rats.");
            state->AddCardBattlefield(Rat);
            id_token = Rat->GetIdObj();
        } else if (obj->GetKeyWord().compare("TokenSquirrel") == 0) {
            std::shared_ptr<Etat::Creature> Squirrel(new Etat::Creature(1, 1, true, "Ecureuil", coutVide, capaVide, state->GetInd(), obj->GetIndJoueur()));
            Squirrel->SetOracle("Creature Jeton 1/1\nJeton de creature ecureuil,\ncree par Glandee.");
            state->AddCardBattlefield(Squirrel);
            id_token = Squirrel->GetIdObj();
        } else if (obj->GetKeyWord().compare("Folie") == 0)
            engine.lock()->AddCommand(std::shared_ptr<CommandDiscard>(new CommandDiscard(1 - obj->GetIndJoueur())));
        else if (obj->GetKeyWord().compare("Contresort") == 0) {
            for (unsigned int i = 0; i < state->GetPile().size() - 1; i++)
                if (state->GetPile()[i]->GetIdObj() == target->GetIdObj()) {
                    state->DelCardPile(i);
                    if (!target->GetIsCapacite())
                        state->GetJoueurs()[state->GetPile()[i]->GetIndJoueur()]->AddCardGraveyard(std::static_pointer_cast<Etat::Carte>(target));
                        pos_target = i;
                }
        }//state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->AddCardHand(state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary()[state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary().size()-1]);
            //state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->DelCardLibrary( state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary().size()-1);
        state->DelCardPile(state->GetPile().size()-1);
    }

    void CommandResolveCapa::Undo(std::shared_ptr<Etat::State> state) {
        //std::cout<<obj->GetKeyWord()<<" "<<obj->GetKeyWord().compare("blue")<<" "<<obj->GetKeyWord().compare("green")<<std::endl;
        if (obj->GetKeyWord().compare("multi") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetMulti(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetMulti() - 1);
        else if (obj->GetKeyWord().compare("blue") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetBlue(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetBlue() - 1);
        else if (obj->GetKeyWord().compare("green") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetGreen(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetGreen() - 1);
        else if (obj->GetKeyWord().compare("black") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetBlack(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetBlack() - 1);
        else if (obj->GetKeyWord().compare("inc") == 0)
            state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->SetInc(state->GetJoueurs()[obj->GetIndJoueur()]->GetManaPool()->GetInc() - 1);
        else if (obj->GetKeyWord().compare("burn") == 0)
            state->GetJoueurs()[1 - obj->GetIndJoueur()]->SetPv(state->GetJoueurs()[1 - obj->GetIndJoueur()]->GetPv() + 1);
        else if (obj->GetKeyWord().compare("TokenRat") == 0 || obj->GetKeyWord().compare("TokenSquirrel") == 0) {
            for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
                if (state->GetBattlefield()[i]->GetIdObj() == id_token)
                    state->DelCardBattlefield(i);
        } else if (obj->GetKeyWord().compare("Contresort") == 0) {
            if (!target->GetIsCapacite())
                state->GetJoueurs()[target->GetIndJoueur()]->DelCardGraveyard(state->GetJoueurs()[target->GetIndJoueur()]->GetGraveyard().size() - 1);
            // ici ca marche pas : faudra creer une fonction pour inserer dans une pile
            state->GetPile().insert(state->GetPile().begin()+pos_target,target);
        }//state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->AddCardHand(state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary()[state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary().size()-1]);
            //state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->DelCardLibrary( state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary().size()-1);
        state->AddCardPile(obj);
    }

}
