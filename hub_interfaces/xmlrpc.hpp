#include "hub_interface.hpp"

#include <boost/property_tree/ptree.hpp>

#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/girerr.hpp>

#include "basic_hub_interface.hpp"

namespace bunsan{namespace hub_interfaces
{
	class xmlrpc: public bunsan::basic_hub_interface
	{
		typedef xmlrpc_c::registryPtr registry_ptr;
		typedef std::unique_ptr<xmlrpc_c::serverAbyss> server_abyss_ptr;
	public:
		xmlrpc(const boost::property_tree::ptree &config, hub_ptr hub__);
		virtual void serve();
	private:
		hub_ptr hub_;
		registry_ptr registry;
		server_abyss_ptr server;
	};
}}

