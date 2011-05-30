#include "hub_interface.hpp"

#include <thread>

#include <boost/property_tree/ptree.hpp>

#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/girerr.hpp>

#include "runner.hpp"
#include "hub_interface.hpp"

namespace bunsan{namespace dcs{namespace hub_interfaces
{
	class xmlrpc: public bunsan::dcs::hub_interface
	{
		typedef xmlrpc_c::registryPtr registry_ptr;
		typedef std::unique_ptr<xmlrpc_c::serverAbyss> server_abyss_ptr;
	public:
		xmlrpc(const boost::property_tree::ptree &config, hub_ptr hub__);
		virtual void start();
		virtual void wait();
		virtual void stop();
	protected:
		static hub_interface_ptr instance(const boost::property_tree::ptree &config, hub_ptr hub__);
	private:
		hub_ptr hub_;
		registry_ptr registry;
		server_abyss_ptr server;
		std::shared_ptr<std::thread> thread;
		static bunsan::runner reg;
	};
}}}

