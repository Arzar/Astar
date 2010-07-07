#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>


#include "Grid.h"

class Path;

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

struct vertex_position_t 
{
    typedef boost::vertex_property_tag kind;
};


typedef boost::property<vertex_position_t, sf::Vector2f> VertexPositionProperty;
typedef boost::property<boost::edge_weight_t, double > EdgeWeightProperty;

// create a typedef for the Graph type
typedef boost::adjacency_list<boost::vecS, 
	                         boost::vecS, 
							 boost::directedS, 
							 VertexPositionProperty,
							 EdgeWeightProperty
							> Graph;

typedef boost::graph_traits<Graph> GraphTraits;
typedef GraphTraits::vertex_descriptor Vertex;
typedef GraphTraits::edge_descriptor Edge;
typedef GraphTraits::vertex_iterator Vertex_Iter;
typedef GraphTraits::edge_iterator Edge_Iter;

typedef boost::property_map<Graph, vertex_position_t>::type VertexPositionMap;
typedef boost::property_map<Graph, boost::edge_weight_t>::type EdgeWeightMap;

class GraphSolver
{
private:
	
	Graph graph_;
	VertexPositionMap positions_;
    EdgeWeightMap distances_;

	void AddEdges(Grid& grid);
		
	void AddEge(int xVert1, int yVert1, int xVert2, int yVert2, Grid& grid);
	void AddEdgesFourCorner(Grid& grid);
	void AddEdgesFrameLine(Grid& grid);
	void AddEdgesCenter(Grid& grid);

	void PrintGraph(Grid& grid);

public:
	GraphSolver(Grid& grid);
	   	
	Path AstarSolve(int start, int goal);
	Path DijkstraSolve(int start, int goal);
};