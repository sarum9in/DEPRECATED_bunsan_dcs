#ifndef LOCAL_HPP
#define LOCAL_HPP

#include <string>
#include <vector>
#include <map>
#include <mutex>

#include <boost/property_tree/ptree.hpp>

#include "runner.hpp"

#include "hub.hpp"

namespace bunsan{namespace dcs{namespace hubs
{
	class local: public bunsan::dcs::hub
	{
		//typedef unsigned long long capacity_t; // 0 capacity as infinity and alinement with reducing capacity to negative
		typedef long long capacity_t;
		struct resource
		{
			std::string type, uri;
			capacity_t capacity;
		};
		typedef std::shared_ptr<resource> resource_ptr;
		typedef std::weak_ptr<resource> resource_wptr;
	public:
		// construction
		local(const boost::property_tree::ptree &config);
		virtual void clear();
		//virtual void reinit(const boost::property_tree::ptree &config);
		// manipulation
		virtual void remove_resource(const std::string &type, const std::string &uri);
		virtual std::string get_resource(const std::string &type);
		virtual void start();
		virtual void join();
		virtual void stop();
		virtual bool is_running();
		virtual ~local();
	protected:
		virtual void add_resource_(const std::string &type, const std::string &uri, const std::string &capacity);
		virtual void set_capacity_(const std::string &type, const std::string &uri, const std::string &capacity);
		static hub_ptr instance(const boost::property_tree::ptree &config);
	private:
		bool contains(const std::string &type, const std::string &uri);
		std::mutex lock;
		std::map<std::string, std::map<std::string, resource_ptr>> index_type_uri;
		std::map<std::string, std::map<capacity_t, std::map<std::string, resource_wptr>>> index_type_capacity_uri;
		static bunsan::runner reg;
	};
}}}

#endif //LOCAL_HPP

