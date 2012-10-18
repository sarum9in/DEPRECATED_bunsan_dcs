#include "xmlrpc.hpp"

#include <string>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/girerr.hpp>

#include "bunsan/util.hpp"

// factory

bool bunsan::dcs::hub_interfaces::xmlrpc::factory_reg_hook = bunsan::dcs::hub_interface::register_new("xmlrpc",
    [](const boost::property_tree::ptree &config, const bunsan::dcs::hub_ptr &hub__)
    {
        bunsan::dcs::hub_interface_ptr tmp(new bunsan::dcs::hub_interfaces::xmlrpc(config, hub__));
        return tmp;
    });

// virtual class

// hub_container

// machine

namespace
{
    class method_add_machine: public xmlrpc_c::method2
    {
    public:
        method_add_machine(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
        virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
        {
            DLOG();
            try
            {
                std::string machine = param_list.getString(0);
                std::string capacity = param_list.getString(1);
                param_list.verifyEnd(2);
                hub_->add_machine(machine, capacity);
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
                std::string machine = param_list.getString(0);
                std::string capacity = param_list.getString(1);
                param_list.verifyEnd(2);
                hub_->set_capacity(machine, capacity);
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

    class method_remove_machine: public xmlrpc_c::method2
    {
    public:
        method_remove_machine(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
        virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
        {
            DLOG();
            try
            {
                std::string machine = param_list.getString(0);
                param_list.verifyEnd(1);
                hub_->remove_machine(machine);
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

    // resource

    class method_add_resource: public xmlrpc_c::method2
    {
    public:
        method_add_resource(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
        virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
        {
            DLOG();
            try
            {
                std::string machine = param_list.getString(0);
                std::string resource = param_list.getString(1);
                std::string uri = param_list.getString(2);
                param_list.verifyEnd(3);
                hub_->add_resource(machine, resource, uri);
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


    class method_set_resource_uri: public xmlrpc_c::method2
    {
    public:
        method_set_resource_uri(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
        virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
        {
            DLOG();
            try
            {
                std::string machine = param_list.getString(0);
                std::string resource = param_list.getString(1);
                std::string uri = param_list.getString(2);
                param_list.verifyEnd(3);
                hub_->set_resource_uri(machine, resource, uri);
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
                std::string machine = param_list.getString(0);
                std::string resource = param_list.getString(1);
                param_list.verifyEnd(2);
                hub_->remove_resource(machine, resource);
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

    class method_select_resource: public xmlrpc_c::method2
    {
    public:
        method_select_resource(bunsan::dcs::hub_ptr hub__):hub_(hub__){}
        virtual void execute(const xmlrpc_c::paramList &param_list, const xmlrpc_c::callInfo *call_info, xmlrpc_c::value *result)
        {
            DLOG();
            try
            {
                std::string resource = param_list.getString(0);
                param_list.verifyEnd(1);
                *result = xmlrpc_c::value_string(hub_->select_resource(resource));
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
}

void bunsan::dcs::hub_interfaces::xmlrpc::create_server()
{
    server.reset(new xmlrpc_c::serverAbyss(xmlrpc_c::serverAbyss::constrOpt().registryPtr(registry).portNumber(port)));
}

bunsan::dcs::hub_interfaces::xmlrpc::xmlrpc(const boost::property_tree::ptree &config, const hub_ptr &hub__):
    hub_(hub__), port(config.get<unsigned int>("server.port")), registry(new xmlrpc_c::registry)
{
    xmlrpc_c::methodPtr
        add_machine(new method_add_machine(hub_)),
        set_capacity(new method_set_capacity(hub_)),
        remove_machine(new method_remove_machine(hub_)),
        clear(new method_clear(hub_)),
        add_resource(new method_add_resource(hub_)),
        set_resource_uri(new method_set_resource_uri(hub_)),
        remove_resource(new method_remove_resource(hub_)),
        select_resource(new method_select_resource(hub_));
    registry->addMethod("add_machine", add_machine);
    registry->addMethod("set_capacity", set_capacity);
    registry->addMethod("remove_machine", remove_machine);
    registry->addMethod("clear", clear);
    registry->addMethod("add_resource", add_resource);
    registry->addMethod("set_resource_uri", set_resource_uri);
    registry->addMethod("remove_resource", remove_resource);
    registry->addMethod("select_resource", select_resource);
}

bunsan::dcs::hub_ptr bunsan::dcs::hub_interfaces::xmlrpc::hub()
{
    return hub_;
}

