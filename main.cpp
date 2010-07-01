#include "stdafx.h"

#include "Loader.h"
#include "DrawableRegister.h"

#include "ImageManager.h"
#include "Material.h"
#include "Grid.h"
#include "WaypointManager.h"


int main(int argc, char** argv)
{
	Loader loader;
	ImageManager imMgr = loader.LoadImages();
	MaterialManager matMgr = loader.LoadMaterials(imMgr, "material.txt");
	Grid grid = loader.LoadGrid(matMgr, "grid.txt");
	WaypointManager waypointMgr(&grid);
	
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Window");

	DrawableRegister reg;
	reg.AddStatic(grid);

	grid.InitDisplay(App.GetWidth(), App.GetHeight());
	
	while (App.IsOpened())
	{
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			// Fenêtre fermée
			if (Event.Type == sf::Event::Closed)
				App.Close();

			// Touche 'echap' appuyée
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();

			if ((Event.Type == sf::Event::MouseButtonPressed))
			{
				const sf::Input& input = App.GetInput();
				float x = (float)input.GetMouseX();
				float y = (float)input.GetMouseY();

				if(Event.MouseButton.Button == sf::Mouse::Left)
				{
					waypointMgr.AddStartPoint(x, y);
					reg.AddTemp(waypointMgr);
				}

				if(Event.MouseButton.Button == sf::Mouse::Right)
				{
					waypointMgr.AddEndPoint(x, y);
					reg.AddTemp(waypointMgr);
				}
			}
		}

        // Efface l'écran (remplissage avec du noir)
        App.Clear();

		reg.DrawStatic(App);
		reg.DrawTemp(App);

		 // Affichage du contenu de la fenêtre à l'écran
        App.Display();
	}
	return EXIT_SUCCESS;
}


/*
#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>



template <class Graph> 
struct exercise_out_edge
{
	typedef boost::graph_traits<Graph> GraphTraits;
	typedef typename GraphTraits::vertex_descriptor Vertex;
	typedef typename GraphTraits::edge_descriptor Edge;
	typedef typename GraphTraits::vertex_iterator vertex_iter;

	typedef typename boost::property_map<Graph, boost::vertex_index_t>::type Vertex_Index;
	typedef typename GraphTraits::out_edge_iterator Out_Edge_Iter;

    exercise_out_edge(Graph& g_) : g(g_) {}
	void operator()(const Vertex& v) const
    {
		Vertex_Index index = boost::get(boost::vertex_index, g);
		std::cout <<"Vertex : " << index[v] << " ";
  
		std::cout << "out-edges: ";
		Out_Edge_Iter out_i, out_end;
        Edge e;
		for (boost::tie(out_i, out_end) = boost::out_edges(v, g); out_i != out_end; ++out_i) 
		{
			e = *out_i;
			Vertex src = source(e, g);
			Vertex targ = target(e, g);
			std::cout << "(" << index[src] << "," << index[targ] << ") ";
        }
		std::cout << std::endl;
    }
    Graph& g;
};

template <class Graph> 
struct exercise_in_edge
{
	typedef boost::graph_traits<Graph> GraphTraits;
	typedef typename GraphTraits::vertex_descriptor Vertex;
	typedef typename GraphTraits::edge_descriptor Edge;
	typedef typename GraphTraits::vertex_iterator vertex_iter;

	typedef typename boost::property_map<Graph, boost::vertex_index_t>::type Vertex_Index;
	typedef typename GraphTraits::out_edge_iterator Out_Edge_Iter;

    exercise_in_edge(Graph& g_) : g(g_) {}
	void operator()(const Vertex& v) const
    {
		Vertex_Index index = boost::get(boost::vertex_index, g);
		std::cout <<"Vertex : " << index[v] << " ";
  
		std::cout << "out-edges: ";
		Out_Edge_Iter out_i, out_end;
        Edge e;
		for (boost::tie(out_i, out_end) = boost::in_edges(v, g); out_i != out_end; ++out_i) 
		{
			e = *out_i;
			Vertex src = source(e, g);
			Vertex targ = target(e, g);
			std::cout << "(" << index[src] << "," << index[targ] << ") ";
        }
		std::cout << std::endl;
    }
    Graph& g;
};


template <class Graph> 
struct exercise_adjacency_vertex
{
	typedef boost::graph_traits<Graph> GraphTraits;
	typedef typename GraphTraits::vertex_descriptor Vertex;

	typedef typename boost::property_map<Graph, boost::vertex_index_t>::type Vertex_Index;
	typedef typename GraphTraits::adjacency_iterator Adj_Iter;

    exercise_adjacency_vertex(Graph& g_) : g(g_) {}
	void operator()(const Vertex& v) const
    {
		Vertex_Index index = boost::get(boost::vertex_index, g);
		std::cout <<"Vertex : " << index[v] << " ";

		std::cout << "adjacent vertices: ";
		Adj_Iter ai, ai_end;
		for (tie(ai, ai_end) = adjacent_vertices(v, g); ai != ai_end; ++ai)
		{
			std::cout << index[*ai] <<  " ";
		}
		std::cout << std::endl;
    }
    Graph& g;
};


template <class Edge>
class record_predecessors : public boost::dijkstra_visitor<>
{
  public:
	  record_predecessors(std::vector<Edge>& a)
      : m_a(a) { }

    template <class Graph>
    void edge_relaxed(Edge e, Graph& g) {
      // set the parent of the target(e) to source(e)
      m_a.push_back(e);
    }
  protected:
	  std::vector<Edge>& m_a;
};

template <class Edge>
record_predecessors<Edge>
make_predecessor_recorder(std::vector<Edge>& a) 
{
    return record_predecessors<Edge>(a);
}
*/



//int main(int,char*[])
//{
	/*
   // create a typedef for the Graph type
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> Graph;

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

    // declare a graph object
    Graph g(num_vertices);

    // add the edges to the graph object
    for (int i = 0; i < num_edges; ++i)
      add_edge(edge_array[i].first, edge_array[i].second, g);
    

	//get the property map for vertex indices
	typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
	IndexMap index = boost::get(boost::vertex_index, g);

    std::cout << "vertices(g) = ";
	typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
	vertex_iter vi, vi_end;
	for (boost::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
      std::cout << index[*vi] <<  " ";
    std::cout << std::endl;



	std::cout << "edges(g) = ";
	typedef boost::graph_traits<Graph>::edge_iterator edge_iter; 
	edge_iter ei, ei_end;
	for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
	{
		std::cout << "(" << index[boost::source(*ei, g)] 
	              << "," << index[boost::target(*ei, g)] << ") ";
	}
    std::cout << std::endl;


   std::for_each(vertices(g).first, vertices(g).second, exercise_out_edge<Graph>(g));
   //std::for_each(vertices(g).first, vertices(g).second, exercise_in_edge<Graph>(g));
   std::for_each(vertices(g).first, vertices(g).second, exercise_adjacency_vertex<Graph>(g));
   return 0;
   */
/*
	typedef boost::adjacency_list<
		boost::listS, 
		boost::vecS, 
		boost::undirectedS, 
		boost::no_property, 
		boost::property<boost::edge_weight_t, int> 
	> Graph;

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

	Vertex_Index index = boost::get(boost::vertex_index, G);

	// vector for storing distance property
	std::vector<int> d(num_vertices(G));
	
	std::vector<Vertex> p(num_vertices(G), GraphTraits::null_vertex()); //the predecessor array
	std::vector<Edge> a; //the predecessor array

	
	Vertex_Iter vi = *(vertices(G).first);

	std::cout << "Vertex : " << index[*vi] <<  "\n";

	// invoke variant 2 of Dijkstra's algorithm
	boost::dijkstra_shortest_paths(G, *vi, 
		boost::predecessor_map(&p[0]).distance_map(&d[0]).visitor(make_predecessor_recorder(a)));
	
	std::cout << "parents in the tree of shortest paths:" << std::endl;
	GraphTraits::vertex_iterator vi2, vi2_end;
	for(boost::tie(vi2, vi2_end) = boost::vertices(G); vi2 != vi2_end; ++vi2)
	{
		std::cout << "parent(" << *vi2;
		if (p[*vi2] == GraphTraits::null_vertex())
			std::cout << ") = no parent" << std::endl; 
		else 
			std::cout << ") = " << p[*vi2] << std::endl;
	}
	std::cout << std::endl;
	*/
//}



 