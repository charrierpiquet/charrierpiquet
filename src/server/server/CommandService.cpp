#include "CommandService.hpp"


namespace server
{
	CommandService::CommandService (std::vector<Json::Value>& val) : AbstractService("/command"),
    listCommands(val) { }

	HttpStatus CommandService::get (Json::Value& out, int id) const {
	if (id>=0)
	{
		if(id > (int)listCommands.size())
			throw ServiceException(HttpStatus::NOT_FOUND,"Invalid command id");
		else
			for (unsigned int i=id; i<listCommands.size(); i++)
				out.append(listCommands[i]);
		}
		else
			out["Size"] = listCommands.size();
		return HttpStatus::OK;
	}

	HttpStatus CommandService::post (const Json::Value& in, int id) { 
		throw ServiceException(HttpStatus::NOT_FOUND,"Service not found");	
	}

	HttpStatus CommandService::put (Json::Value& out, const Json::Value& in) 
	{
	
		listCommands.push_back(in);
		return HttpStatus::CREATED;
	}

	HttpStatus CommandService::remove (int id) 
	{	
		if (id>0 && id<=(int)listCommands.size())
		{
			listCommands.erase(listCommands.begin() +id);
			return HttpStatus::NO_CONTENT;
		}
		else
		{
			throw ServiceException(HttpStatus::NOT_FOUND,"Invalid command id");
		}
	}
}

