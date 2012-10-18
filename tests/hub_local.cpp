#include "bunsan/dcs/hub.hpp"

#include <boost/property_tree/ptree.hpp>

#include <stdexcept>
#include <iostream>
#include <cassert>

int main(int argc, char **argv)
{
    using namespace std;
    using namespace boost::property_tree;
    using namespace bunsan::dcs;
    ptree config;
    hub_ptr local = hub::instance("local", config);
    local->start();
    local->add_machine("local0", 0);
    try
    {
        local->add_machine("local0", 0);
        assert(false);
    }
    catch (std::exception &e){}
    local->add_resource("local0", "gcc", "gcc0_uri");
    local->add_machine("local1", 0);
    local->add_resource("local1", "gcc", "gcc1_uri");
    string r = local->select_resource("gcc");
    assert(r=="gcc0_uri" || r=="gcc1_uri");
    local->set_capacity("local0", 1);
    assert(local->select_resource("gcc")=="gcc0_uri");
    local->set_capacity("local1", 2);
    assert(local->select_resource("gcc")=="gcc1_uri");
    local->remove_machine("local1");
    assert(local->select_resource("gcc")=="gcc0_uri");
    local->remove_machine("local0");
    try
    {
        local->select_resource("gcc");
        assert(false);
    }
    catch (std::exception &e){}
    local->stop();
}

