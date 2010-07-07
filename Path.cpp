#include "stdafx.h"

#include "Path.h"

Path::Range Path::GetShortestPath() 
{
	return boost::make_iterator_range(shortest_path_.begin(), shortest_path_.end());
}

Path::Range Path::GetAllPath() 
{
	return boost::make_iterator_range(all_path_.begin(), all_path_.end());
}