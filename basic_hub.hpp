#ifndef BASE_HUB_HPP
#define BASE_HUB_HPP

#include <boost/property_tree/ptree.hpp>

#include "util.hpp"

namespace bunsan{namespace dcs
{
	class basic_hub
	{
	public:
		virtual void clear()=0;
		//virtual void reinit(const boost::property_tree::ptree &config)=0;
		virtual void add_resource(const std::string &type, const std::string &uri, const std::string &capacity)=0;
		virtual void remove_resource(const std::string &type, const std::string &uri)=0;
		virtual void set_capacity(const std::string &type, const std::string &uri, const std::string &capacity)=0;
		virtual std::string get_resource(const std::string &type)=0;
		virtual ~basic_hub()=0;
	};
	inline basic_hub::~basic_hub(){};
}}

#endif //BASE_HUB_HPP

