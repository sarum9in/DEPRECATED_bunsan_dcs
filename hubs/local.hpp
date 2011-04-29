#ifndef LOCAL_HPP
#define LOCAL_HPP

#include <string>
#include <vector>
#include <map>
#include <mutex>

#include <boost/property_tree/ptree.hpp>

#include "basic_hub.hpp"

namespace bunsan{namespace hubs
{
	class local: public bunsan::basic_hub
	{
		typedef unsigned long long capacity_t;
		struct resource
		{
			std::string type, uri;
			capacity_t capacity;
		};
		typedef std::shared_ptr<resource> resource_ptr;
		typedef std::weak_ptr<resource> resource_wptr;
	public:
		// non-copyable
		local()=delete;
		local(const local &)=delete;
		local(const local &&)=delete;
		local &operator=(const local &)=delete;
		local &operator=(const local &&)=delete;
		// end non-copyable
		// construction
		local(const boost::property_tree::ptree &config);
		virtual void init(const boost::property_tree::ptree &config);
		// manipulation
		virtual void add_resource(const std::string &type, const std::string &uri, const std::string &capacity);
		virtual void remove_resource(const std::string &type, const std::string &uri);
		virtual void set_capacity(const std::string &type, const std::string &uri, const std::string &capacity);
		virtual std::string get_resource(const std::string &type);
		virtual ~local();
	private:
		std::mutex lock;
		std::map<std::string, std::map<std::string, resource_ptr>> index_type_uri;
		std::map<std::string, std::map<capacity_t, std::map<std::string, resource_wptr>>> index_type_capacity_uri;
	};
}}

#endif //LOCAL_HPP

