#ifndef HUB_INTERFACE_HPP
#define HUB_INTERFACE_HPP

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>

#include "bunsan/service.hpp"
#include "bunsan/factory.hpp"

#include "bunsan/dcs/hub.hpp"

namespace bunsan{namespace dcs
{
	class hub_interface: virtual public bunsan::service, private boost::noncopyable
	BUNSAN_FACTORY_BEGIN(hub_interface, const boost::property_tree::ptree &, const bunsan::dcs::hub_ptr &)
	public:
		virtual bunsan::dcs::hub_ptr hub()=0;
	BUNSAN_FACTORY_END(hub_interface)
}}

#endif //HUB_INTERFACE_HPP

