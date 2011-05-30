#include "hub_interface.hpp"

// factory
std::shared_ptr<std::map<std::string, std::function<bunsan::dcs::hub_interface_ptr(const boost::property_tree::ptree &, bunsan::dcs::hub_ptr)>>> bunsan::dcs::hub_interface::factory;

void bunsan::dcs::hub_interface::register_new(const std::string &type, const std::function<hub_interface_ptr(const boost::property_tree::ptree &, bunsan::dcs::hub_ptr)> f)
{
	if (!factory)
		factory.reset(new std::map<std::string, std::function<hub_interface_ptr(const boost::property_tree::ptree &, bunsan::dcs::hub_ptr)>>);
	if (factory->find(type)==factory->end())
		(*factory)[type] = f;
	else
		throw std::runtime_error("factory \""+type+"\" was already registered");
}

bunsan::dcs::hub_interface_ptr bunsan::dcs::hub_interface::instance(const std::string &type, const boost::property_tree::ptree &config, bunsan::dcs::hub_ptr hub__)
{
	if (factory)
	{
		auto iter = factory->find(type);
		if (iter==factory->end())
		{
			return bunsan::dcs::hub_interface_ptr();
		}
		else
		{
			return iter->second(config, hub__);
		}
	}
	else
	{
		return bunsan::dcs::hub_interface_ptr();
	}
}

