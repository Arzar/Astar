#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

#include "Grid.h"
class GraphSolver
{
	// create a typedef for the Graph type
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

	typedef boost::graph_traits<Graph> GraphTraits;
	typedef GraphTraits::vertex_descriptor Vertex;
	typedef GraphTraits::edge_descriptor Edge;
	typedef GraphTraits::vertex_iterator Vertex_Iter;
	typedef GraphTraits::edge_iterator Edge_Iter;

    typedef std::pair<int,int> E;
	typedef boost::property_map<Graph, boost::vertex_index_t>::type Vertex_Index;


	Graph graph_;
public:
	Graph(Grid& grid)
	{
	}

    // Make convenient labels for the vertices
    enum { A, B, C, D, E, N };
    const int num_vertices = N;
    const char* name = "ABCDE";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    Edge edge_array[] = 
    { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
      Edge(C,E), Edge(B,D), Edge(D,E) };
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);

	typedef boost::graph_traits<Graph> GraphTraits;
	typedef GraphTraits::vertex_descriptor Vertex;
	typedef GraphTraits::edge_descriptor Edge;
	typedef boost::graph_traits<Graph>::vertex_iterator Vertex_Iter;
    typedef std::pair<int,int> E;
	typedef boost::property_map<Graph, boost::vertex_index_t>::type Vertex_Index;

    const int num_nodes = 5;
    E edges[] = { E(0,2), 
                  E(1,1), E(1,3), E(1,4),
                  E(2,1), E(2,3), 
                  E(3,4),
                  E(4,0), E(4,1) };
    int weights[] = { 1, 2, 1, 2, 7, 3, 1, 1, 1};

    Graph G(edges, edges + sizeof(edges) / sizeof(E), weights, num_nodes);

};