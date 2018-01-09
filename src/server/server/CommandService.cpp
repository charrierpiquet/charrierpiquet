#include "CommandeService.hpp"


namespace server
{
	
	
	
UserService::UserService (Game& gm) : AbstractService("/user"),
    game(gm) { }

HttpStatus UserService::get (Json::Value& out, int id) const {
	if (id>=0)
	{
		if(id > ListeCommandes.size())
		{
			throw ServiceException(HttpStatus::NOT_FOUND,"Invalid command id");
		}
		else
		{
			for (int i=id; i<ListeCommandes.size(); i++)
			{
				out.push_back(ListeCommandes[i]);
			}
		}
	}
	else
	{
		out["Size"] = ListeCommande.size();
    }
    return HttpStatus::OK;
}

HttpStatus UserService::post (const Json::Value& in, int id) {
    
}

HttpStatus UserService::put (int id,const Json::Value& in) {
	
	ListeCommandes.push_back(in);
	return HttpStatus::CREATED;
	}

HttpStatus UserService::remove (int id) {
	
	if (id>0 && id<=ListeCommandes.size())
	{
		ListeCommandes.erase(id);
		return HttpStatus::NO_CONTENT;
	}
	else
	{
		throw ServiceException(HttpStatus::NOT_FOUND,"Invalid command id");
	}

}

}

