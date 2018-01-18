#include "CommandService.hpp"
#include <iostream>

namespace server
{
	CommandService::CommandService (std::shared_ptr<Engine::Moteur>& m) : AbstractService("/command"),
    moteur(m) { }

	HttpStatus CommandService::get (Json::Value& out, int id) const {
		if (id>=0)
		{
			if(id >= moteur->HistoricSize())
				throw ServiceException(HttpStatus::NOT_FOUND,"Invalid command id");
			else
			{
				//std::cout<<id<<" "<<moteur.HistoricSize() -1<<std::endl;
				for (int i=id; i < moteur->HistoricSize(); i++)
				{
					//std::cout<<"ici ?"<<std::endl;
					auto machin = moteur->GetCommand(i);
					out.append(machin);
				}
				//std::cout<<"et la ça marche ?"<<std::endl;
			}
		}
		else
			out["Size"] = moteur->HistoricSize();
		return HttpStatus::OK;
	}

	HttpStatus CommandService::post (const Json::Value& in, int id) { 
		throw ServiceException(HttpStatus::NOT_FOUND,"Service not found");	
	}

	HttpStatus CommandService::put (Json::Value& out, const Json::Value& in) 
	{
		moteur->ReadCommand(in);
		return HttpStatus::CREATED;
	}

	HttpStatus CommandService::remove (int id) 
	{	
			moteur->RollBack();
			return HttpStatus::NO_CONTENT;
	}
}

