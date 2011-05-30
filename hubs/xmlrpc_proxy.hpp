#ifndef XMLRPC_PROXY_HPP
#define XMLRPC_PROXY_HPP

#include <boost/property_tree/ptree.hpp>

#include "runner.hpp"
#include "hub.hpp"

namespace bunsan{namespace dcs{namespace hubs
{
	class xmlrpc_proxy: public bunsan::dcs::hub
	{
	public:
		// construction
		xmlrpc_proxy(const boost::property_tree::ptree &config);
		// manipulation
		virtual void clear();
		virtual void remove_resource(const std::string &type, const std::string &uri);
		virtual std::string get_resource(const std::string &type);
		virtual void start();
		virtual void wait();
		virtual void stop();
		virtual ~xmlrpc_proxy();
	protected:
		virtual void add_resource_(const std::string &type, const std::string &uri, const std::string &capacity);
		virtual void set_capacity_(const std::string &type, const std::string &uri, const std::string &capacity);
		static hub_ptr instance(const boost::property_tree::ptree &config);
	private:
		const std::string server_url;
		static bunsan::runner reg;
	};
}}}

#endif //XMLRPC_PROXY_HPP

