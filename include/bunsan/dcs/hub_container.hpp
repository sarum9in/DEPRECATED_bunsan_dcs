#ifndef HUB_CONTAINER_HPP
#define HUB_CONTAINER_HPP

#include "bunsan/util.hpp"

namespace bunsan{namespace dcs
{
	class hub_container
	{
	public:
		/*!
		 * \brief add new machine
		 * 
		 * machine can be assumed as a resource group
		 *
		 * \param machine machine name
		 * \param capacity machine's capacity
		 */
		template <typename I>
		void add_machine(const std::string &machine, const I &capacity)
		{
			SLOG(machine<<' '<<capacity);
			this->add_machine_(machine, get_integer(capacity));
		}
		/*!
		 * \brief set machine's capacity
		 *
		 * \param machine machine name
		 * \param capacity machine's capacity
		 */
		template <typename I>
		void set_capacity(const std::string &machine, const I &capacity)
		{
			SLOG(machine<<' '<<capacity);
			this->set_capacity_(machine, get_integer(capacity));
		}
		/*!
		 * \brief remove machine and all resources it has
		 */
		virtual void remove_machine(const std::string &machine)=0;
		/*!
		 * \brief add resource to machine
		 */
		virtual void add_resource(const std::string &machine, const std::string &resource, const std::string &uri)=0;
		/*!
		 * \brief set resource uri
		 */
		virtual void set_resource_uri(const std::string &machine, const std::string &resource, const std::string &uri)=0;
		/*!
		 * \brief remove resource from machine
		 */
		virtual void remove_resource(const std::string &machine, const std::string &resource)=0;
		/*!
		 * \brief select most preferable resource uri
		 */
		virtual std::string select_resource(const std::string &resource)=0;
		/*!
		 * \brief clear all info from hub
		 */
		virtual void clear()=0;
		virtual inline ~hub_container(){}
	protected:
		virtual void add_machine_(const std::string &machine, const std::string &capacity)=0;
		virtual void set_capacity_(const std::string &machine, const std::string &capacity)=0;
		template <typename I>
		static std::string get_integer(const I &integer_);
	};
	template <typename I>
	std::string hub_container::get_integer(const I &integer_)
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
			bool has_sign = integer[0]=='+' || integer[0]=='-';
			auto i = integer.cbegin();
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
}}

#endif //HUB_CONTAINER_HPP

