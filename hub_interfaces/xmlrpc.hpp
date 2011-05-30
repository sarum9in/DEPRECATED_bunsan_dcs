#include "hub_interface.hpp"

#include <thread>
#include <mutex>

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
		typedef std::shared_ptr<xmlrpc_c::serverAbyss> server_ptr;
	public:
		xmlrpc(const boost::property_tree::ptree &config, hub_ptr hub__);
		virtual bunsan::dcs::hub_ptr hub();
		virtual void start();
		virtual void join();
		virtual void stop();
		virtual bool is_running();
	protected:
		static hub_interface_ptr instance(const boost::property_tree::ptree &config, hub_ptr hub__);
	private:
		typedef std::unique_lock<std::mutex> guard;
		void create_server();
		void run();
		std::mutex lock;
		unsigned port;
		hub_ptr hub_;
		registry_ptr registry;
		server_ptr server;
		//std::shared_ptr<std::thread> thread;
		std::thread thread;
		// factory
		static bunsan::runner reg;
	};
}}}

