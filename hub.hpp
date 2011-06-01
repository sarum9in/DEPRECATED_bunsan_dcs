#ifndef HUB_HPP
#define HUB_HPP

#include <memory>
#include <functional>
#include <string>
#include <map>

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "service.hpp"

#include "hub_container.hpp"

namespace bunsan{namespace dcs
{
	class hub: public hub_container, public bunsan::service, private boost::noncopyable
	{
	public:
		// factory
		typedef std::shared_ptr<hub> hub_ptr;
		static hub_ptr instance(const std::string &type, const boost::property_tree::ptree &config);
	protected:
		static void register_new(const std::string &type, const std::function<hub_ptr(const boost::property_tree::ptree &)> f);
	private:
		static std::shared_ptr<std::map<std::string, std::function<hub_ptr(const boost::property_tree::ptree &)>>> factory;
	};
	typedef hub::hub_ptr hub_ptr;
}}

#endif //HUB_HPP

