#include "xmlrpc_proxy.hpp"

#include <xmlrpc-c/client_simple.hpp>

#include "util.hpp"

bunsan::dcs::hubs::xmlrpc_proxy::xmlrpc_proxy(const boost::property_tree::ptree &config):server_url(config.get<std::string>("server_url"))
{
	SLOG("created proxy for bunsan::dcs::hub_interface::xmlrpc with address \""<<server_url<<"\"");
}

void bunsan::dcs::hubs::xmlrpc_proxy::clear()
{
	xmlrpc_c::clientSimple proxy;
	xmlrpc_c::value result;
	proxy.call(server_url, "clear", xmlrpc_c::paramList(), &result);
}

void bunsan::dcs::hubs::xmlrpc_proxy::add_resource(const std::string &type, const std::string &uri, const std::string &capacity)
{
	xmlrpc_c::clientSimple proxy;
	xmlrpc_c::value result;
	proxy.call(server_url, "add_resource", xmlrpc_c::paramList().addc(type).addc(uri).addc(capacity), &result);
}

void bunsan::dcs::hubs::xmlrpc_proxy::remove_resource(const std::string &type, const std::string &uri)
{
	xmlrpc_c::clientSimple proxy;
	xmlrpc_c::value result;
	proxy.call(server_url, "remove_resource", xmlrpc_c::paramList().addc(type).addc(uri), &result);
}

void bunsan::dcs::hubs::xmlrpc_proxy::set_capacity(const std::string &type, const std::string &uri, const std::string &capacity)
{
	xmlrpc_c::clientSimple proxy;
	xmlrpc_c::value result;
	proxy.call(server_url, "set_capacity", xmlrpc_c::paramList().addc(type).addc(uri).addc(capacity), &result);
}

std::string bunsan::dcs::hubs::xmlrpc_proxy::get_resource(const std::string &type)
{
	xmlrpc_c::clientSimple proxy;
	xmlrpc_c::value result;
	proxy.call(server_url, "get_resource", xmlrpc_c::paramList().addc(type), &result);
	return xmlrpc_c::value_string(result).cvalue();
}

bunsan::dcs::hubs::xmlrpc_proxy::~xmlrpc_proxy()
{
}

