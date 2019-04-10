#include <vector>

struct Restaurant
{
	std::string name;
	std::string category;
	std::string location;
	float rating;


};

struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

struct Edge
{
    vertex *v;
    //int distance;
};

/*this is the struct for each vertex in the graph. */
struct vertex
{
    Restaurant restaurant;
    bool visited;
    std::vector<Edge> Edges; //stores edges to adjacent vertices
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addVertex(std::string restaurantName, std::string category, std::string location, float rating);
    void addEdge(std::string restaurant1, std::string restaurant2);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();
    void recommend(string restaurantName);
    void displayVertex(vertex *v);

  private:
    std::vector<vertex> vertices; //stores vertices

    vertex *findVertex(std::string name);
    void BFT_traversal(vertex *v);
    void DFT_traversal(vertex *v);

};


class User
{
public:
	void saveRestaurant(string restaurantName);
	void getRecommend(string restaurantName);
private:
	string username;
	string password;
	std::vector<Edge> savedRestaurants;
};
