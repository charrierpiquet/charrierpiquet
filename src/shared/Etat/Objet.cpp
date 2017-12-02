#include "Objet.h"

namespace Etat
{
    Objet::Objet(bool capa, int id, int prop, std::string nom, std::shared_ptr<Cout> cout) : cost(cout)
    {
        isCapacite = capa;
        idObj = id;
        indJoueur = prop;
        name = nom;
        //oracle = std::shared_ptr<std::string>(new std::string());
    }
    
    void Objet::SetTarget(std::weak_ptr<Objet> cible)
    {
        target = cible;
    }
    std::weak_ptr<Objet> Objet::GetTarget() const
    {
        return target;
    }
    bool Objet::GetIsCapacite() const
    {
        return isCapacite;
    }
    int Objet::GetIndJoueur() const
    {
        return indJoueur;
    }
    int Objet::GetIdObj() const
    {
        return idObj;
    }
    void Objet::SetOracle(std::string txt)
    {
        oracle = txt;
    }
    std::string Objet::GetOracle() const
    {
        return oracle;
    }
    std::string Objet::GetName() const
    {
        return name;
    }
    std::shared_ptr<Cout> Objet::GetCost()
    {
        return cost;
    }
};

