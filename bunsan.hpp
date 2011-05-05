#ifndef BUNSAN_HPP
#define BUNSAN_HPP

#include <vector>
#include <iostream>

#include <boost/date_time/posix_time/posix_time.hpp>

#define SLOG(M) std::cerr<<"["<<__FILE__<<":"<<__LINE__<<":"<<__func__<<":"<<boost::posix_time::second_clock::local_time()<<"] "<<M<<std::endl
#define DLOG(M) SLOG(#M)

namespace bunsan
{
	//typedef std::vector<unsigned char> bytes;
	/*class id
	{
	public:
		id()=delete;
		inline id(const id &_id):data(_id.data){}
		inline id(const id &&_id)=default;// TODO
		inline explicit id(size_t size=0):data(size){}
		auto inline begin(){return data.begin();}
		auto inline end(){return data.begin();}
		auto inline begin() const {return data.begin();}
		auto inline end() const {return data.begin();}
		auto operator
		}
	private:
		std::vector<unsigned char> data;
	};*/
}

#endif //BUNSAN_HPP

