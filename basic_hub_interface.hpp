#ifndef BASIC_HUB_INTERFACE_HPP
#define BASIC_HUB_INTERFACE_HPP

#include "hub.hpp"

namespace bunsan
{
	class basic_hub_interface
	{
	public:
		//virtual hub_ptr get_hub()=0;
		virtual void serve()=0;
		virtual ~basic_hub_interface()=0;
	};
	inline basic_hub_interface::~basic_hub_interface(){}
}

#endif //BASIC_HUB_INTERFACE_HPP

