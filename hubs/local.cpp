#include "local.hpp"

#include <string>

#include <boost/lexical_cast.hpp>

#include "bunsan.hpp"

typedef std::unique_lock<std::mutex> guard;

bunsan::hubs::local::local(const boost::property_tree::ptree &config)
{
	//TODO
}

void bunsan::hubs::local::clear()
{
	DLOG(clearing hub info);
	index_type_uri.clear();
	index_type_capacity_uri.clear();
}

bunsan::hubs::local::~local()
{
	DLOG(destruction);
}

void bunsan::hubs::local::add_resource(const std::string &type, const std::string &uri, const std::string &capacity)
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
	nr->capacity = boost::lexical_cast<bunsan::hubs::local::capacity_t>(capacity);
	DLOG(created);
	DLOG(adding object to index);
	index_type_uri[nr->type][nr->uri] = nr;
	index_type_capacity_uri[nr->type][nr->capacity][nr->uri] = resource_wptr(nr);
	DLOG(added);
}

void bunsan::hubs::local::remove_resource(const std::string &type, const std::string &uri)
{
	guard lk(lock);
	SLOG(type<<' '<<uri);
	index_type_uri.at(type).erase(uri);
}

std::string bunsan::hubs::local::get_resource(const std::string &type)
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

void bunsan::hubs::local::set_capacity(const std::string &type, const std::string &uri, const std::string &capacity)
{
	guard lk(lock);
	SLOG(type<<' '<<uri<<' '<<capacity);
	bunsan::hubs::local::capacity_t nc = boost::lexical_cast<bunsan::hubs::local::capacity_t>(capacity);
	if (!contains(type, uri))
		throw std::out_of_range("resource \""+type+"\" with uri=\""+uri+"\" was not found");
	index_type_capacity_uri[type][index_type_uri[type][uri]->capacity].erase(uri);
	index_type_uri[type][uri]->capacity = nc;
	index_type_capacity_uri[type][nc][uri] = resource_wptr(index_type_uri[type][uri]);
}

bool bunsan::hubs::local::contains(const std::string &type, const std::string &uri)
{
	auto type_iter = index_type_uri.find(type);
	if (type_iter==index_type_uri.end())
		return false;
	if (type_iter->second.find(uri)==type_iter->second.end())
		return false;
	return true;
}

