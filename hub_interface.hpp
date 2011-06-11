#ifndef HUB_INTERFACE_HPP
#define HUB_INTERFACE_HPP

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>

#include "service.hpp"
#include "factory.hpp"

#include "hub.hpp"

namespace bunsan{namespace dcs
{
	class hub_interface: virtual public bunsan::service, private boost::noncopyable
	{
	public:
		virtual bunsan::dcs::hub_ptr hub()=0;
		// factory
		typedef std::shared_ptr<hub_interface> hub_interface_ptr;
		static inline hub_interface_ptr instance(const std::string &type, const boost::property_tree::ptree &config, bunsan::dcs::hub_ptr hub_)
		{
			return bunsan::factory::instance(factories, type, std::cref(config), std::ref(hub_));
		}
	protected:
		static inline bool register_new(const std::string &type, const std::function<hub_interface_ptr(const boost::property_tree::ptree &, bunsan::dcs::hub_ptr)> f)
		{
			return bunsan::factory::register_new(factories, type, f);
		}
	private:
		static std::map<std::string, std::function<hub_interface_ptr(const boost::property_tree::ptree &, bunsan::dcs::hub_ptr)>> *factories;
	};
	typedef hub_interface::hub_interface_ptr hub_interface_ptr;
}}

#endif //HUB_INTERFACE_HPP

