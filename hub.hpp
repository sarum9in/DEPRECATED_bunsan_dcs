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
	template <typename I>
	std::string get_integer(const I &integer_)
	{
		std::string integer = boost::lexical_cast<std::string>(integer_);
		bool bad = false;
		std::string reason;
		if (integer.empty())
		{
			reason = "empty integer";
			bad = true;
		}
		else
		{
			auto i = integer.begin();
			bool has_sign = integer[0]=='+' || integer[0]=='-';
			if (has_sign)
				++i;
			if (i==integer.end())
			{
				reason = "only sign";
				bad = true;
			}
			else
			{
				if (!all_of(i, integer.end(), boost::algorithm::is_digit()))
				{
					bad = true;
					reason = "non-digit char";
				}
			}
		}
		if (bad)
			throw std::invalid_argument("invalid integer [\""+integer+"\"], reason: \""+reason+"\"");
		return integer;
	}
	/*!
	 * \brief hub adaptor object
	 *
	 * You should create this object and perform all operations through it.
	 * It is non-copyable.
	 */
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
		/*!
		 * \brief reinitializing class, it works like constructor
		 *
		 * not thread-safe, reentrant
		 *
		 * You can't use other functions while reinit or constructor is not completed. The behaviour is undefined.
		 */
		void reinit(const boost::property_tree::ptree &config);
		// manipulation
		/*!
		 * \brief clears all info from hub
		 */
		void clear();
		/*!
		 * \brief adds new resource to hub
		 *
		 * \param type resource type
		 * \param uri resource uri
		 * \param capacity resource capacity
		 */
		template <typename I>
		void add_resource(const std::string &type, const std::string &uri, const I &capacity)
		{
			SLOG(type<<' '<<' '<<uri<<' '<<capacity);
			this->add_resource_(type, uri, get_integer(capacity));
			/*std::string integer = boost::lexical_cast<std::string>(capacity);
			if (!boost::algorithm::all(integer, boost::algorithm::is_digit()))
				throw std::invalid_argument("invalid integer [\""+integer+"\"]");
			this->add_resource_(type, uri, integer);*/
		}
		/*!
		 * \brief removes resource from hub
		 *
		 * \param type resource type
		 * \param uri resource uri
		 */
		void remove_resource(const std::string &type, const std::string &uri);
		/*!
		 * \brief returns some resource uri for specified type
		 *
		 * \param type resource type
		 */
		std::string get_resource(const std::string &type);
		/*!
		 * \brief sets resource capacity
		 *
		 * \brief type resource type
		 * \param uri resource uri
		 * \param capacity resource capacity
		 */
		template <typename I>
		void set_capacity(const std::string &type, const std::string &uri, const I &capacity)
		{
			SLOG(type<<' '<<' '<<uri<<' '<<capacity);
			this->set_capacity_(type, uri, get_integer(capacity));
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

