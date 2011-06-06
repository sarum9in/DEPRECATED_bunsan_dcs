#include "hub_interface.hpp"

#include <thread>
#include <mutex>

#include <boost/property_tree/ptree.hpp>

#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/girerr.hpp>

#include "runner.hpp"
#include "xmlrpc_service.hpp"
#include "hub_interface.hpp"

namespace bunsan{namespace dcs{namespace hub_interfaces
{
	class xmlrpc: virtual public bunsan::dcs::hub_interface, virtual bunsan::xmlrpc_service
	{
		typedef xmlrpc_c::registryPtr registry_ptr;
		typedef std::shared_ptr<xmlrpc_c::serverAbyss> server_ptr;
	public:
		xmlrpc(const boost::property_tree::ptree &config, hub_ptr hub__);
		virtual bunsan::dcs::hub_ptr hub();
	protected:
		virtual void create_server();
		// factory
		static hub_interface_ptr instance(const boost::property_tree::ptree &config, hub_ptr hub__);
	private:
		typedef std::unique_lock<std::mutex> guard;
		std::mutex lock;
		unsigned port;
		registry_ptr registry;
		hub_ptr hub_;
		// factory
		static bunsan::runner reg;
	};
}}}

