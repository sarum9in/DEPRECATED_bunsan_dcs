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

#include "bunsan/service.hpp"
#include "bunsan/factory.hpp"

#include "bunsan/dcs/hub_container.hpp"

namespace bunsan{namespace dcs
{
	class hub: virtual public hub_container, virtual public bunsan::service, private boost::noncopyable
	{
	public:
		// factory
		typedef std::shared_ptr<hub> hub_ptr;
		static inline hub_ptr instance(const std::string &type, const boost::property_tree::ptree &config)
		{
			return bunsan::factory::instance(factories, type, std::cref(config));
		}
	protected:
		static inline bool register_new(const std::string &type, const std::function<hub_ptr(const boost::property_tree::ptree &)> f)
		{
			return bunsan::factory::register_new(factories, type, f);
		}
	private:
		static std::map<std::string, std::function<hub_ptr(const boost::property_tree::ptree &)>> *factories;
	};
	typedef hub::hub_ptr hub_ptr;
}}

#endif //HUB_HPP

