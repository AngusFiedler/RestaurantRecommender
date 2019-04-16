#include <vector>
#include<algorithm>

class vertex;
class Edge;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

class Edge
{
public:
    vertex *v;
    //float distance;
};

/*this is the struct for each vertex in the graph. */
class vertex
{
public:
    std::string name;
    std::string category;
    std::string location;
    float distance;
    float rating;
    bool saved;
    bool visited;
    std::vector<Edge> Edges; //stores edges to adjacent vertices
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addVertex(std::string restaurantName, std::string category, std::string location, float rating, float distance);
    void addEdge(std::string restaurant1, std::string restaurant2);
    void displayEdges();
    void printDFT();
    void printBFT();
    void setAllVerticesUnvisited();
    void recommend(string restaurantName);
    void displayVertex(vertex *v);
    void buildEdges();

  private:
    std::vector<vertex> vertices; //stores vertices

    bool inEdges(vertex *v1, vertex *v2);
    void sortEdges();
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
