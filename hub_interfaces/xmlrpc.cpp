#include "xmlrpc.hpp"

#include <string>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/girerr.hpp>

#include "util.hpp"

// factory

bunsan::runner bunsan::dcs::hub_interfaces::xmlrpc::reg(bunsan::dcs::hub_interface::register_new, "xmlrpc", bunsan::dcs::hub_interfaces::xmlrpc::instance);

bunsan::dcs::hub_interface_ptr bunsan::dcs::hub_interfaces::xmlrpc::instance(const boost::property_tree::ptree &config, hub_ptr hub__)
{
	hub_interface_ptr tmp(new xmlrpc(config, hub__));
	return tmp;
}

// virtual class

class method_clear: public xmlrpc_c::method2
{
public:
	method_clear(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
	virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
	{
		DLOG();
		try
		{
			param_list.verifyEnd(0);
			hub_->clear();
			*result = xmlrpc_c::value_nil();
		}
		catch(std::exception &e)
		{
			SLOG("fault: \""<<e.what()<<"\"");
			throw xmlrpc_c::fault(e.what());
		}
	}
private:
	bunsan::dcs::hub_ptr hub_;
};

class method_add_resource: public xmlrpc_c::method2
{
public:
	method_add_resource(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
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
	bunsan::dcs::hub_ptr hub_;
};

class method_remove_resource: public xmlrpc_c::method2
{
public:
	method_remove_resource(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
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
	bunsan::dcs::hub_ptr hub_;
};

class method_set_capacity: public xmlrpc_c::method2
{
public:
	method_set_capacity(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
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
	bunsan::dcs::hub_ptr hub_;
};

class method_get_resource: public xmlrpc_c::method2
{
public:
	method_get_resource(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
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
	bunsan::dcs::hub_ptr hub_;
};


bunsan::dcs::hub_interfaces::xmlrpc::xmlrpc(const boost::property_tree::ptree &config, hub_ptr hub__):hub_(hub__), registry(new xmlrpc_c::registry)
{
	xmlrpc_c::methodPtr
		clear(new method_clear(hub_)),
		add_resource(new method_add_resource(hub_)),
		remove_resource(new method_remove_resource(hub_)),
		set_capacity(new method_set_capacity(hub_)),
		get_resource(new method_get_resource(hub_));
	registry->addMethod("clear", clear);
	registry->addMethod("add_resource", add_resource);
	registry->addMethod("remove_resource", remove_resource);
	registry->addMethod("set_capacity", set_capacity);
	registry->addMethod("get_resource", get_resource);
	server.reset(new xmlrpc_c::serverAbyss(xmlrpc_c::serverAbyss::constrOpt().registryPtr(registry).portNumber(config.get<unsigned int>("server.port"))));
}

void bunsan::dcs::hub_interfaces::xmlrpc::start()
{
#warning error check
	if (server)
		thread.reset(new std::thread(&xmlrpc_c::serverAbyss::run, &(*server)));
}

void bunsan::dcs::hub_interfaces::xmlrpc::wait()
{
#warning error check
	if (thread)
		thread->join();
}

void bunsan::dcs::hub_interfaces::xmlrpc::stop()
{
#warning error check
	if (server)
		server->terminate();
	if (thread)
		thread->join();
}

