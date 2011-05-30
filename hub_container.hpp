#ifndef HUB_CONTAINER_HPP
#define HUB_CONTAINER_HPP

#include "util.hpp"

namespace bunsan{namespace dcs
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
			auto i = integer.cbegin();
			bool has_sign = integer[0]=='+' || integer[0]=='-';
			if (has_sign)
				++i;
			if (i==integer.cend())
			{
				reason = "only sign";
				bad = true;
			}
			else
			{
				if (!all_of(i, integer.cend(), boost::algorithm::is_digit()))
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
	class hub_container
	{
	public:
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
		}
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
		/*!
		 * \brief removes resource from hub
		 *
		 * \param type resource type
		 * \param uri resource uri
		 */
		virtual void remove_resource(const std::string &type, const std::string &uri)=0;
		/*!
		 * \brief returns some resource uri for specified type
		 *
		 * \param type resource type
		 */
		virtual std::string get_resource(const std::string &type)=0;
		/*!
		 * \brief clears all info from hub
		 */
		virtual void clear()=0;
		virtual inline ~hub_container(){}
	protected:
		virtual void set_capacity_(const std::string &type, const std::string &uri, const std::string &capacity)=0;
		virtual void add_resource_(const std::string &type, const std::string &uri, const std::string &capacity)=0;
	};
}}

#endif //HUB_CONTAINER_HPP

