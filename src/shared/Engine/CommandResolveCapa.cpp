#include "CommandResolveCapa.h"
#include "Moteur.h"
#include "CommandDiscard.h"
#include "CommandDraw.h"
#include <iostream>

namespace Engine {

    CommandResolveCapa::CommandResolveCapa(std::shared_ptr<Etat::Capacite> capa, std::weak_ptr<Moteur> m) {
        ////std::cout<<"\t\tinit resolvecapa"<<std::endl;
        engine = m;
        keyWord = capa->GetKeyWord();
        indProp = capa->GetIndJoueur();
        idCapa = capa->GetIdObj();
        if (capa->GetNeedTarget())
            idTarget = capa->GetTarget().lock()->GetIdObj();
        else
            idTarget = -1;
        //std::cout<<"la"<<std::endl;
    }

    CommandResolveCapa::CommandResolveCapa() {
        //std::cout<<"ici et c'est pas normal"<<std::endl;
    }

    void CommandResolveCapa::Execute(std::shared_ptr<Etat::State> state) {
        ////std::cout<<"\t\texec resolvecapa "<<std::endl;
        std::vector<std::shared_ptr<Etat::Capacite> > capaVide;
        std::shared_ptr<Etat::Cout> coutVide(new Etat::Cout(0, 0, 0, 0, 0));
        //////std::cout<<keyWord<<" "<<keyWord.compare("blue")<<" "<<keyWord.compare("green")<<std::endl;
        if (keyWord.compare("multi") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetMulti(state->GetJoueurs()[indProp]->GetManaPool()->GetMulti() + 1);
        else if (keyWord.compare("blue") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetBlue(state->GetJoueurs()[indProp]->GetManaPool()->GetBlue() + 1);
        else if (keyWord.compare("green") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetGreen(state->GetJoueurs()[indProp]->GetManaPool()->GetGreen() + 1);
        else if (keyWord.compare("black") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetBlack(state->GetJoueurs()[indProp]->GetManaPool()->GetBlack() + 1);
        else if (keyWord.compare("inc") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetInc(state->GetJoueurs()[indProp]->GetManaPool()->GetInc() + 1);
        else if (keyWord.compare("burn") == 0)
            state->GetJoueurs()[1 - indProp]->SetPv(state->GetJoueurs()[1 - indProp]->GetPv() - 1);
        else if (keyWord.compare("draw") == 0) {
            if (!engine.expired())
                engine.lock()->AddCommand(std::shared_ptr<CommandDraw>(new CommandDraw(indProp)));
        } else if (keyWord.compare("TokenRat") == 0) {
            std::shared_ptr<Etat::Creature> Rat(new Etat::Creature(1, 1, true, (std::string)"Rat", coutVide, capaVide, state->GetInd(), indProp));
            Rat->SetOracle("Creature Jeton 1/1\nJeton de creature rat,\ncree par Chef des rats.");
            state->AddCardBattlefield(Rat);
            id_token = Rat->GetIdObj();
        } else if (keyWord.compare("TokenSquirrel") == 0) {
            std::shared_ptr<Etat::Creature> Squirrel(new Etat::Creature(1, 1, true, "Ecureuil", coutVide, capaVide, state->GetInd(), indProp));
            Squirrel->SetOracle("Creature Jeton 1/1\nJeton de creature ecureuil,\ncree par Glandee.");
            state->AddCardBattlefield(Squirrel);
            id_token = Squirrel->GetIdObj();
        } else if (keyWord.compare("Folie") == 0) {
            if (!engine.expired())
                engine.lock()->AddCommand(std::shared_ptr<CommandDiscard>(new CommandDiscard(1 - indProp)));
        } else if (keyWord.compare("Contresort") == 0) {
            std::shared_ptr<Etat::Objet> target;
            for (unsigned int i = 0; i < state->GetPile().size(); i++)
                if (state->GetPile()[i]->GetIdObj() == idTarget)
                    target = state->GetPile()[i];

            for (unsigned int i = 0; i < state->GetPile().size() - 1; i++)
                if (state->GetPile()[i]->GetIdObj() == idTarget) {
                    state->DelCardPile(i);
                    if (!state->GetPile()[i]->GetIsCapacite())
                        state->GetJoueurs()[state->GetPile()[i]->GetIndJoueur()]->AddCardGraveyard(std::static_pointer_cast<Etat::Carte>(target));
                    pos_target = i;
                }
        } else {
            ////std::cout<<"\t\t keyword : "<<keyWord<<" not found"<<std::endl;
        }

        for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
            for (unsigned int j = 0; j < state->GetBattlefield()[i]->GetAbility().size(); j++)
                if (state->GetBattlefield()[i]->GetAbility()[j]->GetIdObj() == idCapa)
                {
                    std::cout<<"ici 1 "<<std::endl;
                    if (state->GetBattlefield()[i]->GetAbility()[j]->GetSource().lock()->GetIsPermanent())
                    {
                        state->DelCardPile(state->GetPile().size() - 1);
                        std::cout <<"ici 2 "<<std::endl;
                    }
                }
    }

    void CommandResolveCapa::Undo(std::shared_ptr<Etat::State> state) {
        ////std::cout<<"\t\tundo resolvecapa"<<std::endl;
        //////std::cout<<keyWord<<" "<<keyWord.compare("blue")<<" "<<keyWord.compare("green")<<std::endl;
        if (keyWord.compare("multi") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetMulti(state->GetJoueurs()[indProp]->GetManaPool()->GetMulti() - 1);
        else if (keyWord.compare("blue") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetBlue(state->GetJoueurs()[indProp]->GetManaPool()->GetBlue() - 1);
        else if (keyWord.compare("green") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetGreen(state->GetJoueurs()[indProp]->GetManaPool()->GetGreen() - 1);
        else if (keyWord.compare("black") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetBlack(state->GetJoueurs()[indProp]->GetManaPool()->GetBlack() - 1);
        else if (keyWord.compare("inc") == 0)
            state->GetJoueurs()[indProp]->GetManaPool()->SetInc(state->GetJoueurs()[indProp]->GetManaPool()->GetInc() - 1);
        else if (keyWord.compare("burn") == 0)
            state->GetJoueurs()[1 - indProp]->SetPv(state->GetJoueurs()[1 - indProp]->GetPv() + 1);
        else if (keyWord.compare("TokenRat") == 0 || keyWord.compare("TokenSquirrel") == 0) {
            for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
                if (state->GetBattlefield()[i]->GetIdObj() == id_token)
                    state->DelCardBattlefield(i);
        } else if (keyWord.compare("Contresort") == 0) {
            std::shared_ptr<Etat::Objet> target;
            for (unsigned int i = 0; i < state->GetPile().size(); i++)
                if (state->GetPile()[i]->GetIdObj() == idTarget)
                    target = state->GetPile()[i];
            if (!target->GetIsCapacite())
                state->GetJoueurs()[target->GetIndJoueur()]->DelCardGraveyard(state->GetJoueurs()[target->GetIndJoueur()]->GetGraveyard().size() - 1);
            // ici ca marche pas : faudra creer une fonction pour inserer dans une pile
            state->GetPile().insert(state->GetPile().begin() + pos_target, target);
        }//state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->AddCardHand(state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary()[state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary().size()-1]);
        //state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->DelCardLibrary( state->GetJoueurs()[state->GetPile()[state->GetPile().size()-1]->GetIndJoueur()]->GetLibrary().size()-1);

        // on recherche la carte sur le champ de bataille qui a lance cette capacite
        for (unsigned int i = 0; i < state->GetBattlefield().size(); i++)
            for (unsigned int j = 0; j < state->GetBattlefield()[i]->GetAbility().size(); j++)
                if (state->GetBattlefield()[i]->GetAbility()[j]->GetIdObj() == idCapa)
                    if (state->GetBattlefield()[i]->GetAbility()[j]->GetSource().lock()->GetIsPermanent())
                        state->AddCardPile(state->GetBattlefield()[i]->GetAbility()[j]);
    }

    Json::Value CommandResolveCapa::Serialize() const {
        Json::Value val;
        val["typeCmd"] = "ResolveCapa";
        val["keyWord"] = keyWord;
        val["idProp"] = indProp;
        val["idTarget"] = idTarget;
        val["idCapa"] = idCapa;
        val["idToken"] = id_token;
        val["posTarget"] = pos_target;

        return val;
    }

    CommandResolveCapa* CommandResolveCapa::Deserialize(const Json::Value& in) {
        keyWord = in["keyWord"].asString();
        indProp = in["idProp"].asInt();
        idTarget = in["idTarget"].asInt();
        idCapa = in["idCapa"].asInt();
        id_token = in["idToken"].asInt();
        pos_target = in["posTarget"].asInt();
        return this;
    }

    void CommandResolveCapa::SetEngine(std::weak_ptr<Engine::Moteur> moteur) {
        engine = moteur;
    }

}
