#include "bunsan/dcs/hub.hpp"

std::map<std::string, std::function<bunsan::dcs::hub_ptr(const boost::property_tree::ptree &)>> *bunsan::dcs::hub::factories;

