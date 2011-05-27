#include "hub.hpp"

#include <string>
#include <stdexcept>

#include "hubs/local.hpp"
#include "hubs/xmlrpc_proxy.hpp"

std::unique_ptr<bunsan::dcs::basic_hub> get_impl(const std::string &type, const boost::property_tree::ptree &config)
{
	if (type=="local")
	{
		return std::unique_ptr<bunsan::dcs::basic_hub>(new bunsan::dcs::hubs::local(config.get_child("config")));
	}
	else if (type=="xmlrpc_proxy")
	{
		return std::unique_ptr<bunsan::dcs::basic_hub>(new bunsan::dcs::hubs::xmlrpc_proxy(config.get_child("config")));
	}
	else
	{
		throw std::out_of_range("\""+type+"\" was not implemented");
	}
}

bunsan::dcs::hub::hub(const boost::property_tree::ptree &config)
{
	const std::string type = config.get<std::string>("type");
	SLOG("trying to create hub implementation \""<<type<<'"');
	if (type=="none")
	{
		DLOG(no implementation was selected: waiting for "reinit" call);
	}
	else
	{
		pimpl = get_impl(type, config);
	}
	/*else if (type=="local")
	{
		pimpl.reset(new bunsan::dcs::hubs::local(config.get_child("config")));
	}
	else
	{
		throw std::out_of_range("\""+type+"\" was not implemented");
	}*/
}

void bunsan::dcs::hub::reinit(const boost::property_tree::ptree &config)
{
	const std::string type = config.get<std::string>("type");
	SLOG("trying to create hub implementation \""<<type<<'"');
	if (type=="none")
	{
		DLOG(no implementation was selected: waiting for "reinit" call);
	}
	else
	{
		pimpl = get_impl(type, config);
	}
}

bunsan::dcs::hub::~hub()
{
	DLOG(hub destruction);
}

void bunsan::dcs::hub::clear()
{
	DLOG(clearing);
	pimpl->clear();
}

void bunsan::dcs::hub::add_resource_(const std::string &type, const std::string &uri, const std::string &capacity)
{
	SLOG(type<<' '<<uri<<' '<<capacity);
	pimpl->add_resource(type, uri, capacity);
}

void bunsan::dcs::hub::remove_resource(const std::string &type, const std::string &uri)
{
	SLOG(type<<' '<<uri);
	pimpl->remove_resource(type, uri);
}

std::string bunsan::dcs::hub::get_resource(const std::string &type)
{
	SLOG(type);
	return pimpl->get_resource(type);
}

void bunsan::dcs::hub::set_capacity_(const std::string &type, const std::string &uri, const std::string &capacity)
{
	SLOG(type<<' '<<uri<<' '<<capacity);
	pimpl->set_capacity(type, uri, capacity);
}

/*
void bunsan::dcs::hub::add_resource(const std::string &type, const std::string &uri);
void bunsan::dcs::hub::remove_resource(const std::string &type, const std::string &uri);
std::string bunsan::dcs::hub::get_resource(const std::string &type);
void bunsan::dcs::hub::set_capacity_(const std::string &type, const std::string &uri, const std::string &capacity);
*/

