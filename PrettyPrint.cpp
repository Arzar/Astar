#include "stdafx.h"

#include "PrettyPrint.h"


template <typename T>
std::ostream& PrintVector(std::ostream& os, const std::vector<T>& v)
{
	BOOST_FOREACH(auto it, v)
	{
		os << *it << "\n";
	}	
	return os;
}