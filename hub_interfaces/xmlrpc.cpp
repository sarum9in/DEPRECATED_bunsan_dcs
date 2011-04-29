#include "xmlrpc.hpp"

#include <string>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/girerr.hpp>

#include "bunsan.hpp"

class method_add_resource: public xmlrpc_c::method2
{
public:
	method_add_resource(bunsan::hub_ptr hub__):hub_(hub__){}
	virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
	{
		DLOG();
		try
		{
			std::string type = param_list.getString(0);
			std::string uri = param_list.getString(1);
			std::string capacity = param_list.getString(2);
			param_list.verifyEnd(3);
			hub_->add_resource(type, uri, capacity);
			*result = xmlrpc_c::value_nil();
		}
		catch(std::exception &e)
		{
			SLOG("fault: \""<<e.what()<<"\"");
			throw xmlrpc_c::fault(e.what());
		}
	}
private:
	bunsan::hub_ptr hub_;
};

class method_remove_resource: public xmlrpc_c::method2
{
public:
	method_remove_resource(bunsan::hub_ptr hub__):hub_(hub__){}
	virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
	{
		DLOG();
		try
		{
			std::string type = param_list.getString(0);
			std::string uri = param_list.getString(1);
			param_list.verifyEnd(2);
			hub_->remove_resource(type, uri);
			*result = xmlrpc_c::value_nil();
		}
		catch(std::exception &e)
		{
			SLOG("fault: \""<<e.what()<<"\"");
			throw xmlrpc_c::fault(e.what());
		}
	}
private:
	bunsan::hub_ptr hub_;
};

class method_set_capacity: public xmlrpc_c::method2
{
public:
	method_set_capacity(bunsan::hub_ptr hub__):hub_(hub__){}
	virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
	{
		DLOG();
		try
		{
			std::string type = param_list.getString(0);
			std::string uri = param_list.getString(1);
			std::string capacity = param_list.getString(2);
			param_list.verifyEnd(3);
			hub_->set_capacity(type, uri, capacity);
			*result = xmlrpc_c::value_nil();
		}
		catch(std::exception &e)
		{
			SLOG("fault: \""<<e.what()<<"\"");
			throw xmlrpc_c::fault(e.what());
		}
	}
private:
	bunsan::hub_ptr hub_;
};

class method_get_resource: public xmlrpc_c::method2
{
public:
	method_get_resource(bunsan::hub_ptr hub__):hub_(hub__){}
	virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
	{
		DLOG();
		try
		{
			std::string type = param_list.getString(0);
			param_list.verifyEnd(1);
			*result = xmlrpc_c::value_string(hub_->get_resource(type));
		}
		catch(std::exception &e)
		{
			SLOG("fault: \""<<e.what()<<"\"");
			throw xmlrpc_c::fault(e.what());
		}
	}
private:
	bunsan::hub_ptr hub_;
};


bunsan::hub_interfaces::xmlrpc::xmlrpc(const boost::property_tree::ptree &config, hub_ptr hub__):hub_(hub__), registry(new xmlrpc_c::registry)
{
	xmlrpc_c::methodPtr
		add_resource(new method_add_resource(hub_)),
		remove_resource(new method_remove_resource(hub_)),
		set_capacity(new method_set_capacity(hub_)),
		get_resource(new method_get_resource(hub_));
	registry->addMethod("add_resource", add_resource);
	registry->addMethod("remove_resource", remove_resource);
	registry->addMethod("set_capacity", set_capacity);
	registry->addMethod("get_resource", get_resource);
	server.reset(new xmlrpc_c::serverAbyss(xmlrpc_c::serverAbyss::constrOpt().registryPtr(registry).portNumber(config.get<unsigned int>("server.port"))));
}

void bunsan::hub_interfaces::xmlrpc::serve()
{
	server->run();
}

