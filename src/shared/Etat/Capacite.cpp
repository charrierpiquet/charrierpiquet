#include "Capacite.h"
#include "iostream"

namespace Etat
{
    Capacite::Capacite(std::shared_ptr<Cout> cout, std::string motclef, int id, int prop, std::string nom, bool target, std::weak_ptr<Carte> origine):Objet(true, id, prop, nom,cout)
    {
        keyWord = motclef;
        needTarget = target;
        source = origine;
    }
    
    std::string Capacite::GetKeyWord() const
    {
        return keyWord;
    }
    bool Capacite::GetNeedTarget() const
    {
        return needTarget;
    }
    std::weak_ptr<Carte> Capacite::GetSource() const
    {
		return source;
	}
	void Capacite::SetSource(std::weak_ptr<Carte> origine)
	{
		source = origine;
	}
  
};
