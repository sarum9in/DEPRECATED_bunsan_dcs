#ifndef LOCAL_HPP
#define LOCAL_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <mutex>
#include <condition_variable>

#include <boost/property_tree/ptree.hpp>

#include "bunsan/pseudo_service.hpp"

#include "bunsan/dcs/hub.hpp"

namespace bunsan{namespace dcs{namespace hubs
{
	class local: virtual public bunsan::dcs::hub, virtual public bunsan::pseudo_service
	{
		typedef long long capacity_t;
		struct machine_t
		{
			std::string machine;
			capacity_t capacity;
			std::map<std::string, std::string> resource_uri;
		};
		typedef std::shared_ptr<machine_t> machine_ptr;
		typedef std::weak_ptr<machine_t> machine_wptr;
	public:
		// construction
		local(const boost::property_tree::ptree &config);
		virtual ~local();
		//virtual void reinit(const boost::property_tree::ptree &config);
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
	protected:
		virtual void add_machine_(const std::string &machine, const std::string &capacity);
		virtual void set_capacity_(const std::string &machine, const std::string &capacity);
	private:
		typedef std::unique_lock<std::mutex> guard;
		std::mutex lock;
		bool running;
		std::mutex run_lock;
		std::condition_variable joiner;
		std::map<std::string, machine_ptr> machines;
		std::map<std::string, std::multimap<capacity_t, machine_wptr, std::greater<capacity_t>>> resources;
		static bool factory_reg_hook;
	};
}}}

#endif //LOCAL_HPP

