#pragma once
#include <vector>
#include <utility>
#include <boost/range.hpp>

class Path
{
public:

	typedef std::pair<int, int> Edge;
	typedef boost::iterator_range<std::vector<Edge>::iterator> Range;

private:
	std::vector<Edge> shortest_path_;
	std::vector<Edge> all_path_;

public:

	template <typename GraphEdge>
	void SetShortestPath_Edge(const std::vector<GraphEdge>& shortest_path)
	{
		shortest_path_.clear();
		BOOST_FOREACH(GraphEdge e, shortest_path)
		{
			shortest_path_.push_back(std::make_pair(e.m_source, e.m_target));
		}
	}

	template <typename GraphEdge>
	void SetAllPath_Edge(const std::vector<GraphEdge>& all_path)
	{
		all_path_.clear();
		BOOST_FOREACH(GraphEdge e, all_path)
		{
			all_path_.push_back(std::make_pair(e.m_source, e.m_target));
		}
	}

	
	template <typename Vertex>
	void SetShortestPath_Vertex(const std::vector<Vertex>& shortest_path)
	{
		shortest_path_.clear();
		for(unsigned int i1 = 0, i2 = 1 ; i2 < shortest_path.size() ; i1 ++ , i2++)
		{
			shortest_path_.push_back(std::make_pair(shortest_path[i1], shortest_path[i2]));
		}
	}
	
	template <typename Vertex>
	void SetAllPath_Vertex(const std::vector<Vertex>& all_path)
	{
		for(unsigned int i1 = 0, i2 = 1 ; i2 < all_path.size() ; i1 ++ , i2++)
		{
			all_path_.push_back(std::make_pair((int)all_path[i1], (int)all_path[i2]));
		}
	}

	Range GetShortestPath();
	Range GetAllPath();
};