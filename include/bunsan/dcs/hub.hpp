#ifndef BUNSAN_DCS_HUB_HPP
#define BUNSAN_DCS_HUB_HPP

#include <memory>
#include <functional>
#include <string>
#include <map>

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "bunsan/service.hpp"
#include "bunsan/factory_helper.hpp"

#include "bunsan/dcs/hub_container.hpp"

namespace bunsan{namespace dcs
{
    class hub: virtual public hub_container, virtual public bunsan::service, private boost::noncopyable
    BUNSAN_FACTORY_BEGIN(hub, const boost::property_tree::ptree &)
    BUNSAN_FACTORY_END(hub)
}}

#endif //BUNSAN_DCS_HUB_HPP

