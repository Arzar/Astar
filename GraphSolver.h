#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>


#include "Grid.h"


struct Node
{
	sf::Vector2f pos;
};

// Une liaison entre deux waypoints
struct NodeConnection
{
	NodeConnection():dist(0.0f), weight(0.0f)
	{

	}

	float dist;
	float weight;
    // idem
};


// create a typedef for the Graph type
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Node, NodeConnection> Graph;

typedef boost::graph_traits<Graph> GraphTraits;
typedef GraphTraits::vertex_descriptor Vertex;
typedef GraphTraits::edge_descriptor Edge;
typedef GraphTraits::vertex_iterator Vertex_Iter;
typedef GraphTraits::edge_iterator Edge_Iter;

typedef boost::property_map<Graph, boost::vertex_index_t>::type Vertex_Index;

class GraphSolver
{
private:
	
	Graph graph_;
	void AddEdges(Grid& grid);
		
	void AddEge(int xVert1, int yVert1, int xVert2, int yVert2, Grid& grid);
	void AddEdgesFourCorner(Grid& grid);
	void AddEdgesFrameLine(Grid& grid);
	void AddEdgesCenter(Grid& grid);

	void PrintGraph(Grid& grid);

public:
	GraphSolver(Grid& grid);
	   	
	std::vector<Vertex> AstarSolve(int start, int goal);
	std::vector<Vertex> DijkstraSolve(int start, int goal);
};