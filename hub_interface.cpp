#include "bunsan/dcs/hub_interface.hpp"

std::map<std::string, std::function<bunsan::dcs::hub_interface_ptr(const boost::property_tree::ptree &, bunsan::dcs::hub_ptr)>> *bunsan::dcs::hub_interface::factories;

