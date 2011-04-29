#ifndef HUB_INTERFACE_HPP
#define HUB_INTERFACE_HPP

#include <boost/property_tree/ptree.hpp>

#include "hub.hpp"
#include "basic_hub_interface.hpp"

namespace bunsan
{
	class hub_interface
	{
	public:
		//non-copyable
		hub_interface()=delete;
		hub_interface(const hub_interface &)=delete;
		hub_interface(const hub_interface &&)=delete;
		hub_interface &operator=(const hub_interface &)=delete;
		hub_interface &operator=(const hub_interface &&)=delete;
		//end non-copyable
		explicit hub_interface(const boost::property_tree::ptree &config, hub_ptr);
		~hub_interface();
		void serve();
	private:
		std::unique_ptr<bunsan::basic_hub_interface> pimpl;
	};
}

#endif //HUB_INTERFACE_HPP

