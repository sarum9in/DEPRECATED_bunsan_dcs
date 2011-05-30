#include "local.hpp"

#include <string>

#include <boost/lexical_cast.hpp>

// factory

bunsan::runner bunsan::dcs::hubs::local::reg(bunsan::dcs::hub::register_new, "local", bunsan::dcs::hubs::local::instance);

bunsan::dcs::hub_ptr bunsan::dcs::hubs::local::instance(const boost::property_tree::ptree &config)
{
	hub_ptr tmp(new local(config));
	return tmp;
}

// virtual class

typedef std::unique_lock<std::mutex> guard;

bunsan::dcs::hubs::local::local(const boost::property_tree::ptree &config)
{
#warning empty constructor
}

void bunsan::dcs::hubs::local::clear()
{
	DLOG(clearing hub info);
	index_type_uri.clear();
	index_type_capacity_uri.clear();
}

bunsan::dcs::hubs::local::~local()
{
	DLOG(destruction);
}

#warning not defined
void bunsan::dcs::hubs::local::start(){}

void bunsan::dcs::hubs::local::join(){}

void bunsan::dcs::hubs::local::stop(){}

bool bunsan::dcs::hubs::local::is_running()
{
#warning not defined
	return true;
}

void bunsan::dcs::hubs::local::add_resource_(const std::string &type, const std::string &uri, const std::string &capacity)
{
	guard lk(lock);
	SLOG(type<<' '<<uri<<' '<<capacity);
	DLOG(checking resource existance);
	if (contains(type, uri))
		throw std::out_of_range("resource \""+type+"\" with uri=\""+uri+"\" has already been inserted");
	DLOG(creating resource object);
	resource_ptr nr(new resource);
	nr->type = type;
	nr->uri = uri;
	nr->capacity = boost::lexical_cast<bunsan::dcs::hubs::local::capacity_t>(capacity);
	DLOG(created);
	DLOG(adding object to index);
	index_type_uri[nr->type][nr->uri] = nr;
	index_type_capacity_uri[nr->type][nr->capacity][nr->uri] = resource_wptr(nr);
	DLOG(added);
}

void bunsan::dcs::hubs::local::remove_resource(const std::string &type, const std::string &uri)
{
	guard lk(lock);
	SLOG(type<<' '<<uri);
	index_type_uri.at(type).erase(uri);
}

std::string bunsan::dcs::hubs::local::get_resource(const std::string &type)
{
	guard lk(lock);
	SLOG(type);
	auto current = index_type_capacity_uri.at(type).rbegin();
	auto end = index_type_capacity_uri.at(type).rend();
	while (current!=end)
	{
		while (!current->second.empty() && current->second.begin()->second.expired())
		{
			SLOG("found orphan [\""<<type<<"\", \""<<current->second.begin()->first<<"\"] resource, removing");
			current->second.erase(current->second.begin());
		}
		if (!current->second.empty())
		{
			SLOG("found \""<<current->second.begin()->second.lock()->uri<<'"');
			return current->second.begin()->second.lock()->uri;
		}
		++current;
	}
	SLOG("resource \""<<type<<"\" was not found");
	throw std::out_of_range("resource \""+type+"\" was not found");
}

void bunsan::dcs::hubs::local::set_capacity_(const std::string &type, const std::string &uri, const std::string &capacity)
{
	guard lk(lock);
	SLOG(type<<' '<<uri<<' '<<capacity);
	bunsan::dcs::hubs::local::capacity_t nc = boost::lexical_cast<bunsan::dcs::hubs::local::capacity_t>(capacity);
	if (!contains(type, uri))
		throw std::out_of_range("resource \""+type+"\" with uri=\""+uri+"\" was not found");
	index_type_capacity_uri[type][index_type_uri[type][uri]->capacity].erase(uri);
	index_type_uri[type][uri]->capacity = nc;
	index_type_capacity_uri[type][nc][uri] = resource_wptr(index_type_uri[type][uri]);
}

bool bunsan::dcs::hubs::local::contains(const std::string &type, const std::string &uri)
{
	auto type_iter = index_type_uri.find(type);
	if (type_iter==index_type_uri.end())
		return false;
	if (type_iter->second.find(uri)==type_iter->second.end())
		return false;
	return true;
}

