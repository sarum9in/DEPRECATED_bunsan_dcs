#ifndef XMLRPC_PROXY_HPP
#define XMLRPC_PROXY_HPP

#include <boost/property_tree/ptree.hpp>

#include "bunsan/pseudo_service.hpp"

#include "bunsan/dcs/hub.hpp"

namespace bunsan{namespace dcs{namespace hubs
{
	class xmlrpc_proxy: virtual public bunsan::dcs::hub, virtual public bunsan::pseudo_service
	{
	public:
		// construction
		xmlrpc_proxy(const boost::property_tree::ptree &config);
		// manipulation
		// hub_container
		// machine
		virtual void remove_machine(const std::string &machine);
		virtual void clear();
		// resource
		virtual void add_resource(const std::string &machine, const std::string &resource, const std::string &uri);
		virtual void set_resource_uri(const std::string &machine, const std::string &resource, const std::string &uri);
		virtual void remove_resource(const std::string &machine, const std::string &resource);
		// select
		virtual std::string select_resource(const std::string &resource);
		// service
		virtual ~xmlrpc_proxy();
	protected:
		virtual void add_machine_(const std::string &machine, const std::string &capacity);
		virtual void set_capacity_(const std::string &machine, const std::string &capacity);
	private:
		const std::string server_url;
		static bool factory_reg_hook;
	};
}}}

#endif //XMLRPC_PROXY_HPP

