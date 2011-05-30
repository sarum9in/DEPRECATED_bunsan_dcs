#include "hub.hpp"

// factory
std::shared_ptr<std::map<std::string, std::function<bunsan::dcs::hub_ptr(const boost::property_tree::ptree &)>>> bunsan::dcs::hub::factory;

void bunsan::dcs::hub::register_new(const std::string &type, const std::function<hub_ptr(const boost::property_tree::ptree &)> f)
{
	if (!factory)
		factory.reset(new std::map<std::string, std::function<hub_ptr(const boost::property_tree::ptree &)>>);
	if (factory->find(type)==factory->end())
		(*factory)[type] = f;
	else
		throw std::runtime_error("factory \""+type+"\" was already registered");
}

bunsan::dcs::hub_ptr bunsan::dcs::hub::instance(const std::string &type, const boost::property_tree::ptree &config)
{
	if (factory)
	{
		auto iter = factory->find(type);
		if (iter==factory->end())
		{
			return hub_ptr();
		}
		else
		{
			return iter->second(config);
		}
	}
	else
	{
		return hub_ptr();
	}
}

