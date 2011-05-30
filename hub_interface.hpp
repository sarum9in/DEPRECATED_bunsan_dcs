#ifndef HUB_INTERFACE_HPP
#define HUB_INTERFACE_HPP

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>

#include "hub.hpp"
#include "service.hpp"

namespace bunsan{namespace dcs
{
	class hub_interface: public service, private boost::noncopyable
	{
	public:
		// factory
		typedef std::shared_ptr<hub_interface> hub_interface_ptr;
		static hub_interface_ptr instance(const std::string &type, const boost::property_tree::ptree &config, bunsan::dcs::hub_ptr hub__);
	protected:
		static void register_new(const std::string &type, const std::function<hub_interface_ptr(const boost::property_tree::ptree &, bunsan::dcs::hub_ptr)> f);
	private:
		static std::shared_ptr<std::map<std::string, std::function<hub_interface_ptr(const boost::property_tree::ptree &, bunsan::dcs::hub_ptr)>>> factory;
	};
	typedef hub_interface::hub_interface_ptr hub_interface_ptr;
}}

#endif //HUB_INTERFACE_HPP

