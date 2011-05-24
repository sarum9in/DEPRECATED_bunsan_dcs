#ifndef HUB_INTERFACE_HPP
#define HUB_INTERFACE_HPP

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>

#include "hub.hpp"
#include "basic_hub_interface.hpp"

namespace bunsan
{
	class hub_interface: private boost::noncopyable
	{
	public:
		explicit hub_interface(const boost::property_tree::ptree &config, hub_ptr);
		~hub_interface();
		void serve();
	private:
		std::unique_ptr<bunsan::basic_hub_interface> pimpl;
	};
}

#endif //HUB_INTERFACE_HPP

