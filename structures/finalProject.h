#include <vector>
#include <algorithm>

class vertex;

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
    int count;
    float weight;
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
    //void printDFT();
    //void printBFT();
    //void setAllVerticesUnvisited();
    void recommend();
    void displayVertex(vertex *v);
    void buildEdges();
    void saveRestaurant(string restaurantName);

  private:
    std::vector<vertex> vertices; //stores vertices

    std::vector<vertex*> savedRestaurants;

    bool inEdges(vertex *v1, vertex *v2);
    bool inRecommendations(vertex *v, vector<vertex*> recommendations);
    void setWeights(vector<vertex*> recommendations);
    void sortRecommendations();
    vertex *findVertex(std::string name);

    float calcWeight(vertex *v);
    //void BFT_traversal(vertex *v);
    //void DFT_traversal(vertex *v);

};


// class User
// {
// public:
//     Graph g0;
// 	void saveRestaurant(string restaurantName);
// 	void getRecommend(string restaurantName);
// private:
// 	// string username;
// 	// string password;
// 	std::vector<vertex> savedRestaurants;
// };
