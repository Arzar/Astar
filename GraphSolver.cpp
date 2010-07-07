#include "stdafx.h"
#include "GraphSolver.h"

#include <boost/graph/astar_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "Path.h"

GraphSolver::GraphSolver(Grid& grid)
{
   positions_ = get(vertex_position_t(), graph_);
   distances_ = get(boost::edge_weight, graph_);

   int num_nodes = grid.GetNbCol() * grid.GetNbRow();

	for (int i = 0 ; i < num_nodes; i++)
	{
		Vertex v = boost::add_vertex(graph_);
		boost::put(positions_, v, grid.GetBoxByNumber(i).GetCenter());
	}
	
	AddEdges(grid);
}


void GraphSolver::AddEge(int xVert1, int yVert1, int xVert2, int yVert2, Grid& grid)
{
	Edge e;
	bool b;
	boost::tie(e, b) = boost::add_edge(grid.Lin(xVert1, yVert1), grid.Lin(xVert2, yVert2), graph_);
	if(b == false)
	{
		assert(0);
	}
	
	float weight = grid.GetBoxByRank(xVert2, yVert2).GetSpeedFactor();
	float dist = sf::distance(sf::Vector2f((float)xVert1, (float)yVert1), sf::Vector2f((float)xVert2, (float)yVert2));
	
	distances_[e] = weight * dist; 

}

void GraphSolver::AddEdgesFourCorner(Grid& grid)
{
	int x = grid.GetNbCol() -1;
	int y = grid.GetNbRow() -1;

	AddEge(0, 0, 1, 0, grid);
	AddEge(0, 0, 1, 1, grid);
	AddEge(0, 0, 0, 1, grid);
	
	// top right box
	AddEge(x, 0, x-1, 0, grid);
	AddEge(x, 0, x-1, 1, grid);
	AddEge(x, 0, x, 1, grid);

	// bottom right box
	AddEge(x, y, x, y-1, grid);
	AddEge(x, y, x-1, y-1, grid);
	AddEge(x, y, x-1, y, grid);
	
	// bottom left box
	AddEge(0, y, 0, y-1, grid);
	AddEge(0, y, 1, y-1, grid);
	AddEge(0, y, 1, y, grid);
}
	

void GraphSolver::AddEdgesFrameLine(Grid& grid)
{
	int x = grid.GetNbCol() -1;
	int y = grid.GetNbRow() -1;

	for(int i = 1 ; i < x ; i++)
	{
		// top line
		AddEge(i, 0, i-1, 0, grid);
		AddEge(i, 0, i+1, 0, grid);
		AddEge(i, 0, i-1, 1, grid);
		AddEge(i, 0, i, 1, grid);
		AddEge(i, 0, i+1, 1, grid);
		
		// botom line
		AddEge(i, y, i-1, y, grid);
		AddEge(i, y, i+1, y, grid);
		AddEge(i, y, i-1, y-1, grid);
		AddEge(i, y, i, y-1, grid);
		AddEge(i, y, i+1, y-1, grid);
	}

	for(int j = 1 ; j < y ; j++)
	{
		// left line
		AddEge(0, j, 0, j-1, grid);
		AddEge(0, j, 0, j+1, grid);
		AddEge(0, j, 1, j-1, grid);
		AddEge(0, j, 1, j, grid);
		AddEge(0, j, 1, j+1, grid);

		// right line
		AddEge(x, j, x, j-1, grid);
		AddEge(x, j, x, j+1, grid);
		AddEge(x, j, x-1, j-1, grid);
		AddEge(x, j, x, j, grid);
		AddEge(x, j, x, j+1, grid);
	}
}

void GraphSolver::AddEdgesCenter(Grid& grid)
{
	int x = grid.GetNbCol();
	int y = grid.GetNbRow();

	for(int i = 1 ; i < x - 1 ; i++)
	{
		for(int j = 1 ; j < y - 1; j++)
		{
			AddEge(i, j, i-1, j-1, grid);
			AddEge(i, j, i, j-1, grid);
			AddEge(i, j, i+1, j-1, grid);
			AddEge(i, j, i-1, j, grid);
			AddEge(i, j, i+1, j, grid);
			AddEge(i, j, i-1, j+1, grid);
			AddEge(i, j, i, j+1, grid);
			AddEge(i, j, i+1, j+1, grid);
		}
	}
}

void GraphSolver::PrintGraph(Grid& grid)
{
	Edge_Iter ei = edges(graph_).first;
	Edge_Iter eie = edges(graph_).second;

	for(; ei != eie ; ei++)
	{
		int s = boost::source(*ei, graph_);
		int t = boost::target(*ei, graph_);

		int x_s = s % grid.GetNbCol();
		int y_s = s / grid.GetNbCol();

		int x_t = t % grid.GetNbCol();
		int y_t = t / grid.GetNbCol();

		std::cout << "[" << x_s << " " << y_s << "] --- [" << x_t << " " << y_t << "]\n";
	}
}

void GraphSolver::AddEdges(Grid& grid)
{
	int x = grid.GetNbCol();
	int y = grid.GetNbRow();

	assert(x >= 3);
	assert(y >= 3);

	AddEdgesFourCorner(grid);
	AddEdgesFrameLine(grid);
	AddEdgesCenter(grid);

	//PrintGraph(grid);
}


// Une instance de cette structure sera lancée en exception quand on aura trouvé un chemin
struct found_goal {};
 
// Le visiteur, dont le but est de définir une fonction examine_vertex qui dit si on est arrivé au but.
// Le but est spécifié via le constructeur.
class astar_goal_visitor : public boost::default_astar_visitor{
public:
    astar_goal_visitor(Vertex goal, std::vector<Edge>& allPath) : goal_(goal), allPath_(allPath) {}
 
    void examine_vertex(Vertex v, const Graph& g)  // Le const est important.
	{
        if(v == goal_)
            throw found_goal(); // On sort en lancant une exception. C'est moche mais c'est comme ça.
        }

	void edge_relaxed(Edge e, const Graph& g)
	{
		allPath_.push_back(e);
	}

private:
    Vertex goal_;
	std::vector<Edge>& allPath_;
};

class distance_heuristic : public boost::astar_heuristic <Graph, float>{
public:
    distance_heuristic(const Graph& g, const VertexPositionMap& positions,  Vertex goal)
    : m_graph(g), m_pos(positions), m_goal(goal) {}
 
    float operator()(Vertex v)
    {
		sf::Vector2f v_pos = boost::get(m_pos, v);
		sf::Vector2f goal_pos = boost::get(m_pos, m_goal);
		
		return sf::distance(v_pos, goal_pos);
    }
private:
    const Graph& m_graph;
	const VertexPositionMap& m_pos;
    Vertex m_goal;
};


Path GraphSolver::AstarSolve(int start, int goal)
{
   std::vector<Vertex> p(boost::num_vertices(graph_)); // predecessor

   std::vector<Vertex> shortest_path;
   std::vector<Edge> all_path;
 
	try 
	{ 
		boost::astar_search
		(
			graph_, 
			start,  
			distance_heuristic(graph_, positions_,  goal), // default heuristic
			boost::predecessor_map(&p[0]).
			visitor(astar_goal_visitor(goal, all_path))

			
		);
 
	} 
	catch(found_goal fg) 
	{ 
		for(Vertex v = goal;; v = p[v]) 
		{
	        shortest_path.push_back(v);
		    if(p[v] == v)
			    break;
		}
	}
	std::reverse(shortest_path.begin(), shortest_path.end());

	Path path;
	path.SetShortestPath_Vertex(shortest_path);
	path.SetAllPath_Edge(all_path);

	return path;
}


template <class Edge>
class record_all_path : public boost::dijkstra_visitor<>
{
  public:
	  record_all_path(std::vector<Edge>& a)
      : m_a(a) { }

    template <class Graph>
    void edge_relaxed(Edge e, Graph& g) 
	{
      m_a.push_back(e);
    }
  protected:
	  std::vector<Edge>& m_a;
};

template <class Edge>
record_all_path<Edge>
make_all_path_recorder(std::vector<Edge>& a) 
{
    return record_all_path<Edge>(a);
}


Path GraphSolver::DijkstraSolve(int start, int goal)
{
   std::vector<Vertex> shortest_path;


   std::vector<Vertex> p(num_vertices(graph_), GraphTraits::null_vertex()); //the predecessor array
   std::vector<Edge> all_path; //the predecessor array
	
	boost::dijkstra_shortest_paths(graph_, start,
		boost::predecessor_map(&p[0]).
		visitor(make_all_path_recorder(all_path)));


	for(Vertex v = goal;; v = p[v]) 
	{
	    shortest_path.push_back(v);
		if(p[v] == v)
		   break;
	}

	std::reverse(shortest_path.begin(), shortest_path.end());

	Path path;
	path.SetShortestPath_Vertex(shortest_path);
	path.SetAllPath_Edge(all_path);
 
	return path;
}

