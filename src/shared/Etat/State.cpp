#include "State.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <ctime> 
#include <cstdlib>
#define NbPhase 5
#define MaxHand 7
namespace Etat {

    State::State(std::vector<std::string> list_deck) {
        for (unsigned int i = 0; i < list_deck.size(); i++)
            joueurs.push_back(std::shared_ptr<Joueur>(new Joueur()));
        joueur = 0;
        phase = 0;
        priorite = 0;
        //load

        std::string Type = "";
        std::string Nom = "";
        std::string strCout = "";
        std::string Force = "";
        std::string Endurance = "";
        std::string NbCapa = "";
        std::string Ability = "";
        std::string Texte = "";
        std::string Ligne = "";
        std::vector<std::shared_ptr< Capacite> > Capacites;
        unsigned int Joueur;

        std::vector<std::vector<std::shared_ptr< Carte> > > decks;

        for (Joueur = 0; Joueur < list_deck.size(); Joueur++) {
            int TailleDeck = 0;
            std::ifstream FichierDeck;
            FichierDeck.open("./res/" + list_deck[Joueur] + ".deck");
            std::cout << "chargement deck " << Joueur << " ..." << std::endl;

            if (!FichierDeck)
                std::cout << "impossible d'ouvrir le deck" << std::endl;

            while (FichierDeck.peek() != EOF) {
                TailleDeck++;
                std::getline(FichierDeck, Nom);
                Nom.erase(Nom.end() - 1);
                std::ifstream Card("./res/cartes/" + Nom + ".carte");
                //std::ifstream Card("./res/cartes/Ours.carte");
                if (!Card)
                    std::cout << "impossible d'ouvrir la carte " << Nom << std::endl;
                else {
                    std::getline(Card, Type); //Type.erase(Type.end()-1);
                    std::getline(Card, Nom); //Nom.erase(Nom.end()-1);
                    std::getline(Card, strCout); //Cout.erase(Cout.end()-1);
                    std::getline(Card, Force); //Force.erase(Force.end()-1);
                    std::getline(Card, Endurance); //Endurance.erase(Endurance.end()-1);
                    std::getline(Card, NbCapa); //NbCapa.erase(NbCapa.end()-1);                

                    int k = std::stoi(NbCapa, nullptr, 0), f = std::stoi(Force, nullptr, 0), e = std::stoi(Endurance, nullptr, 0);
                    Capacites.clear();
                    if (k != 0)
                        for (int i = 0; i < k; i++) {
                            std::getline(Card, Ability);
                            std::shared_ptr<Cout> CostAbility(new  Cout(0,Ability[0] - '0', Ability[4] - '0', Ability[2] - '0', Ability[6] - '0'));
                            Capacites.push_back(std::shared_ptr< Capacite>(new  Capacite(CostAbility, Ability.substr(20, Ability.size() - 20), id++, Joueur, Ability.substr(20, Ability.size() - 20), (bool)(int) (Ability[18] - '0'))));
                        }

                    std::shared_ptr<Cout> Cost(new Cout(0, strCout[0] - '0', strCout[4] - '0', strCout[2] - '0', strCout[6] - '0'));
                    if (std::strcmp(Type.data(), "creature") == 0) {
                        decks[Joueur].push_back(std::shared_ptr< Creature>(new  Creature(f, e, false, Nom, Cost, Capacites, id++, Joueur)));
                    } else {
                        decks[Joueur].push_back(std::shared_ptr< Carte>(new  Carte(std::strcmp(Type.data(), "sort") != 0, std::strcmp(Type.data(), "terrain") == 0, std::strcmp(Type.data(), "creature") == 0, 0, Nom, Cost, Capacites, id++, Joueur)));
                    }

                    Texte = "";
                    while (Card.peek() != EOF) {
                        getline(Card, Ligne);
                        Texte = Texte + Ligne + "\n";
                    }
                    decks[Joueur][TailleDeck - 1]->SetOracle(Texte);

                    Card.close();
                }
            }
            FichierDeck.close();
        }
        for (unsigned int i = 0; i < list_deck.size(); i++) {
            std::srand(unsigned ( std::time(0)));
            while (!decks[i].empty()) {
                int k = std::rand() % decks[i].size();
                this->GetJoueurs()[i]->AddCardLibrary(decks[i][k]);
                decks[i].erase(decks[i].begin() + k);
            }
        }
    }

    void State::SetPriority(int value) {
        priorite = std::max(0, std::min(value, (int)joueurs.size()));
    }

    void State::SetPhase(int value) {
        phase = std::max(0, std::min(value, NbPhase - 1));
    }

    void State::AddCardBattlefield(std::shared_ptr<Carte> card) {
        battlefield.push_back(card);
    }

    void State::AddCardPile(std::shared_ptr<Objet> card) {
        pile.push_back(card);
    }

    void State::DelCardBattlefield(int ind) {
        if (ind >= 0 && ind < (int) battlefield.size())
            battlefield.erase(battlefield.begin() + ind);
    }

    void State::DelCardPile(int ind) {
        if (ind >= 0 && ind < (int) pile.size())
            pile.erase(pile.begin() + ind);
    }

    std::vector<std::shared_ptr<Joueur> > State::GetJoueurs() const {
        return joueurs;
    }

    int State::GetPhase() const {
        return phase;
    }

    int State::GetPriority() const {
        return priorite;
    }

    std::vector<std::shared_ptr<Objet> > State::GetPile() const {
        return pile;
    }

    std::vector<std::shared_ptr<Carte> > State::GetBattlefield() const {
        return battlefield;
    }

    std::string State::GetPhaseName() const {
        switch (phase) {
            case 0:
                return "Pre-Combat Main";
            case 1:
                return "Declaration Attaquant";
            case 2:
                return "Priorite combat";
            case 3:
                return "Declaration Bloqueurs";
            case 4:
                return "Post-Combat Main";
            default:
                return "Unknow";
        }
    }

    int State::GetJoueurTour() const {
        return joueur;
    }

    void State::AddListAttaquant(std::shared_ptr<Creature> crea) {
        list_attaquant.push_back(crea);
    }

    std::vector<std::shared_ptr<Creature> > State::GetAttaquants() const {
        return list_attaquant;
    }

    void State::AddListBloqueur(std::shared_ptr<Creature> crea) {
        list_bloqueur.push_back(crea);
    }

    std::vector<std::shared_ptr<Creature> > State::GetBloqueur() const {
        return list_bloqueur;
    }

    void State::AddListBloque(std::shared_ptr<Creature> crea) {
        list_bloque.push_back(crea);
    }

    std::vector<std::shared_ptr<Creature> > State::GetListBloque() const {
        return list_bloque;
    }

    int State::GetInd()
    {
        return id++;
    }
    void State::SetTour(int value)
    {
        joueur = value;
    }
}
