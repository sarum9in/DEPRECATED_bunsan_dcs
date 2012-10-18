#include "local.hpp"

#include <string>

#include <boost/lexical_cast.hpp>

// factory

bool bunsan::dcs::hubs::local::factory_reg_hook = bunsan::dcs::hub::register_new("local",
    [](const boost::property_tree::ptree &config)
    {
        bunsan::dcs::hub_ptr tmp(new bunsan::dcs::hubs::local(config));
        return tmp;
    });

// virtual class

bunsan::dcs::hubs::local::local(const boost::property_tree::ptree &config)
{
    running = false;
}

bunsan::dcs::hubs::local::~local()
{
    DLOG(destruction);
}

// hub_container

void bunsan::dcs::hubs::local::add_machine_(const std::string &machine, const std::string &capacity)
{
    guard lk(lock);
    SLOG(machine<<' '<<capacity);
    capacity_t capacity_ = boost::lexical_cast<capacity_t>(capacity);
    machine_ptr machine_(new machine_t);
    machine_->capacity = capacity_;
    if (machines.find(machine)!=machines.end())
        throw std::out_of_range("machine \""+machine+"\" was already created");
    machines[machine] = machine_;
}

void bunsan::dcs::hubs::local::set_capacity_(const std::string &machine, const std::string &capacity)
{
    guard lk(lock);
    SLOG(machine<<' '<<capacity);
    capacity_t capacity_ = boost::lexical_cast<capacity_t>(capacity);
    auto iter = machines.find(machine);
    if (iter==machines.end())
        throw std::out_of_range("machine \""+machine+"\" was not found");
    std::swap(iter->second->capacity, capacity_);// now capacity_ contains old value, it may be useful
    for (const auto &r: iter->second->resource_uri)
    {
        resources[r.first].insert(std::make_pair(iter->second->capacity, machine_wptr(iter->second)));
    }
}

void bunsan::dcs::hubs::local::remove_machine(const std::string &machine)
{
    guard lk(lock);
    SLOG(machine);
    auto iter = machines.find(machine);
    if (iter==machines.end())
        throw std::out_of_range("machine \""+machine+"\" was not found");
    machines.erase(iter);
}

void bunsan::dcs::hubs::local::clear()
{
    guard lk(lock);
    DLOG();
    machines.clear();
    resources.clear();
}

// resource

void bunsan::dcs::hubs::local::add_resource(const std::string &machine, const std::string &resource, const std::string &uri)
{
    guard lk(lock);
    SLOG(machine<<' '<<resource<<' '<<uri);
    auto iter = machines.find(machine);
    if (iter==machines.end())
        throw std::out_of_range("machine \""+machine+"\" was not found");
    if (iter->second->resource_uri.find(resource)!=iter->second->resource_uri.end())
        throw std::out_of_range("resource \""+resource+"\" was already inserted in \""+machine+"\"");
    iter->second->resource_uri[resource] = uri;
    resources[resource].insert(std::make_pair(iter->second->capacity, machine_wptr(iter->second)));
}

void bunsan::dcs::hubs::local::set_resource_uri(const std::string &machine, const std::string &resource, const std::string &uri)
{
    guard lk(lock);
    SLOG(machine<<' '<<resource<<' '<<uri);
    auto iter = machines.find(machine);
    if (iter==machines.end())
        throw std::out_of_range("machine \""+machine+"\" was not found");
    auto riter = iter->second->resource_uri.find(resource);
    if (riter==iter->second->resource_uri.end())
        throw std::out_of_range("resource \""+resource+"\" was not found in \""+machine+"\"");
    riter->second = uri;
}

void bunsan::dcs::hubs::local::remove_resource(const std::string &machine, const std::string &resource)
{
    guard lk(lock);
    SLOG(machine<<' '<<resource);
    auto iter = machines.find(machine);
    if (iter==machines.end())
        throw std::out_of_range("machine \""+machine+"\" was not found");
    if (iter->second->resource_uri.find(resource)==iter->second->resource_uri.end())
        throw std::out_of_range("resource \""+machine+"\" was not found");
    iter->second->resource_uri.erase(resource);
}

// select

std::string bunsan::dcs::hubs::local::select_resource(const std::string &resource)
{
    guard lk(lock);
    SLOG(resource);
    auto iter = resources.find(resource);
    bool changed;
    do
    {
        changed = false;
        while (iter!=resources.end() && !iter->second.empty() && iter->second.begin()->second.expired())
        {
            changed = true;
            SLOG("found orphan resource \""<<iter->first<<"\", removing");
            iter->second.erase(iter->second.begin());
        }
        if (iter!=resources.end() && !iter->second.empty())
        {
            machine_ptr machine = iter->second.begin()->second.lock(); // should not be expired since we checked it above
            if (machine->resource_uri.find(resource)==machine->resource_uri.end())
            {
                changed = true;
                SLOG("found orphan resource \""<<iter->first<<"\", removing");
                iter->second.erase(iter->second.begin());
                continue;
            }
        }
        if (iter!=resources.end() && !iter->second.empty())
        {
            machine_ptr machine = iter->second.begin()->second.lock(); // see previous
            if (machine->capacity!=iter->second.begin()->first)
            {
                changed = true;
                SLOG("found orphan resource \""<<iter->first<<"\", removing");
                iter->second.erase(iter->second.begin());
                continue;
            }
        }
    } while (changed);
    if (iter==resources.end() || iter->second.empty() || iter->second.begin()->second.expired())// last condition is not needed
        throw std::out_of_range("resource \""+resource+"\" was not found");
    return iter->second.begin()->second.lock()->resource_uri.at(resource);
}

