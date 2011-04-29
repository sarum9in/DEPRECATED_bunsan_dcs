#ifndef HUB_HPP
#define HUB_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <utility>

#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "bunsan.hpp"

#include "basic_hub.hpp"

namespace bunsan
{
	class hub
	{
	public:
		// non-copyable
		hub()=delete;
		hub(const hub &)=delete;
		hub(const hub &&)=delete;
		hub &operator=(const hub &)=delete;
		hub &operator=(const hub &&)=delete;
		// end non-copyable
		// construction
		explicit hub(const boost::property_tree::ptree &config);
		void init(const boost::property_tree::ptree &config);
		// manipulation
		template <typename I>
		void add_resource(const std::string &type, const std::string &uri, const I &capacity)
		{
			SLOG(type<<' '<<' '<<uri<<' '<<capacity);
			std::string integer = boost::lexical_cast<std::string>(capacity);
			if (!boost::algorithm::all(integer, boost::algorithm::is_digit()))
				throw std::invalid_argument("invalid integer [\""+integer+"\"]");
			this->add_resource_(type, uri, integer);
		}
		void remove_resource(const std::string &type, const std::string &uri);
		std::string get_resource(const std::string &type);
		template <typename I>
		void set_capacity(const std::string &type, const std::string &uri, const I &capacity)
		{
			SLOG(type<<' '<<' '<<uri<<' '<<capacity);
			std::string integer = boost::lexical_cast<std::string>(capacity);
			if (!boost::algorithm::all(integer, boost::algorithm::is_digit()))
				throw std::invalid_argument("invalid integer [\""+integer+"\"]");
			this->set_capacity_(type, uri, integer);
		}
		~hub();
	private:
		void set_capacity_(const std::string &type, const std::string &uri, const std::string &capacity);
		void add_resource_(const std::string &type, const std::string &uri, const std::string &capacity);
		std::unique_ptr<bunsan::basic_hub> pimpl;
	};
	typedef std::shared_ptr<hub> hub_ptr;
}

#endif //HUB_HPP

