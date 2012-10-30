#include "xmlrpc_proxy.hpp"

#include <xmlrpc-c/client_simple.hpp>

#include "bunsan/util.hpp"

// factory

const bool bunsan::dcs::hubs::xmlrpc_proxy::factory_reg_hook = bunsan::dcs::hub::register_new("xmlrpc_proxy", 
    [](const boost::property_tree::ptree &config)
    {
        bunsan::dcs::hub_ptr tmp(new bunsan::dcs::hubs::xmlrpc_proxy(config));
        return tmp;
    });

/*bunsan::runner bunsan::dcs::hubs::xmlrpc_proxy::reg(bunsan::dcs::hub::register_new, "xmlrpc_proxy",
    std::function<bunsan::dcs::hub_ptr(const boost::property_tree::ptree &)>([](const boost::property_tree::ptree &config)->bunsan::dcs::hub_ptr
    {
        bunsan::dcs::hub_ptr tmp(new bunsan::dcs::hubs::xmlrpc_proxy(config));
        return tmp;
    }));
*/
// virtual class

bunsan::dcs::hubs::xmlrpc_proxy::xmlrpc_proxy(const boost::property_tree::ptree &config):server_url(config.get<std::string>("server_url"))
{
    SLOG("created proxy for bunsan::dcs::hub_interface::xmlrpc with address \""<<server_url<<"\"");
}

bunsan::dcs::hubs::xmlrpc_proxy::~xmlrpc_proxy()
{
}

// hub_container

// machine

void bunsan::dcs::hubs::xmlrpc_proxy::add_machine_(const std::string &machine, const std::string &capacity)
{
    xmlrpc_c::clientSimple proxy;
    xmlrpc_c::value result;
    proxy.call(server_url, "add_machine", xmlrpc_c::paramList().addc(machine).addc(capacity), &result);
}

void bunsan::dcs::hubs::xmlrpc_proxy::set_capacity_(const std::string &machine, const std::string &capacity)
{
    xmlrpc_c::clientSimple proxy;
    xmlrpc_c::value result;
    proxy.call(server_url, "set_capacity", xmlrpc_c::paramList().addc(machine).addc(capacity), &result);
}

void bunsan::dcs::hubs::xmlrpc_proxy::remove_machine(const std::string &machine)
{
    xmlrpc_c::clientSimple proxy;
    xmlrpc_c::value result;
    proxy.call(server_url, "remove_machine", xmlrpc_c::paramList().addc(machine), &result);
}

void bunsan::dcs::hubs::xmlrpc_proxy::clear()
{
    xmlrpc_c::clientSimple proxy;
    xmlrpc_c::value result;
    proxy.call(server_url, "clear", xmlrpc_c::paramList(), &result);
}

// resource

void bunsan::dcs::hubs::xmlrpc_proxy::add_resource(const std::string &machine, const std::string &resource, const std::string &uri)
{
    xmlrpc_c::clientSimple proxy;
    xmlrpc_c::value result;
    proxy.call(server_url, "add_resource", xmlrpc_c::paramList().addc(machine).addc(resource).addc(uri), &result);
}

void bunsan::dcs::hubs::xmlrpc_proxy::set_resource_uri(const std::string &machine, const std::string &resource, const std::string &uri)
{
    xmlrpc_c::clientSimple proxy;
    xmlrpc_c::value result;
    proxy.call(server_url, "set_resource_uri", xmlrpc_c::paramList().addc(machine).addc(resource).addc(uri), &result);
}

void bunsan::dcs::hubs::xmlrpc_proxy::remove_resource(const std::string &machine, const std::string &resource)
{
    xmlrpc_c::clientSimple proxy;
    xmlrpc_c::value result;
    proxy.call(server_url, "remove_resource", xmlrpc_c::paramList().addc(machine).addc(resource), &result);
}

std::string bunsan::dcs::hubs::xmlrpc_proxy::select_resource(const std::string &resource)
{
    xmlrpc_c::clientSimple proxy;
    xmlrpc_c::value result;
    proxy.call(server_url, "get_resource", xmlrpc_c::paramList().addc(resource), &result);
    return xmlrpc_c::value_string(result).cvalue();
}

