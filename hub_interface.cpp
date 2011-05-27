#include "hub_interface.hpp"

#include <string>
#include <stdexcept>

#include "hub_interfaces/xmlrpc.hpp"

bunsan::dcs::hub_interface::hub_interface(const boost::property_tree::ptree &config, hub_ptr hub_)
{
	std::string type = config.get<std::string>("type");
	if (type=="xmlrpc")
	{
		pimpl.reset(new bunsan::dcs::hub_interfaces::xmlrpc(config.get_child("config"), hub_));
	}
	else
	{
		throw std::out_of_range("\""+type+"\" was not implemented");
	}
}

bunsan::dcs::hub_interface::~hub_interface()
{
}

void bunsan::dcs::hub_interface::serve()
{
	pimpl->serve();
}

