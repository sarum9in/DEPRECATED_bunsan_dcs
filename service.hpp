#ifndef SERVICE_HPP
#define SERVICE_HPP

namespace bunsan{namespace dcs
{
	class service
	{
	public:
		virtual void start()=0;
		virtual void wait()=0;
		virtual void stop()=0;
	};
}}

#endif //SERVICE_HPP

