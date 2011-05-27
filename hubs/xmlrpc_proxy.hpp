#ifndef XMLRPC_PROXY_HPP
#define XMLRPC_PROXY_HPP

#include <boost/property_tree/ptree.hpp>

#include "basic_hub.hpp"

namespace bunsan{namespace dcs{namespace hubs
{
	class xmlrpc_proxy: public bunsan::dcs::basic_hub
	{
	public:
		// non-copyable
		xmlrpc_proxy()=delete;
		xmlrpc_proxy(const xmlrpc_proxy &)=delete;
		xmlrpc_proxy(const xmlrpc_proxy &&)=delete;
		xmlrpc_proxy &operator=(const xmlrpc_proxy &)=delete;
		xmlrpc_proxy &operator=(const xmlrpc_proxy &&)=delete;
		// end non-copyable
		// construction
		xmlrpc_proxy(const boost::property_tree::ptree &config);
		// manipulation
		virtual void clear();
		virtual void add_resource(const std::string &type, const std::string &uri, const std::string &capacity);
		virtual void remove_resource(const std::string &type, const std::string &uri);
		virtual void set_capacity(const std::string &type, const std::string &uri, const std::string &capacity);
		virtual std::string get_resource(const std::string &type);
		virtual ~xmlrpc_proxy();
	private:
		const std::string server_url;
	};
}}}

#endif //XMLRPC_PROXY_HPP

