#pragma once
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"



template<typename T>
struct myPtr
{
	typedef boost::shared_ptr<T> my_ptr ;
};