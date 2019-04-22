#include <vector>
#include <algorithm>
#include <fstream>
#include "JSON.h"

class vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

class Edge
{
public:
    vertex *v;
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

class jsonVertex
{
public:
    std::string name;
    std::string category;
    std::string location;
    float distance;
    float rating;

//     std::string name2;
//     std::string category2;
//     std::string location2;
//     float distance2;
//     float rating2;

//     std::string name3;
//     std::string category3;
//     std::string location3;
//     float distance3;
//     float rating3;

//     std::string name4;
//     std::string category4;
//     std::string location4;
//     float distance4;
//     float rating4;

//     std::string name5;
//     std::string category5;
//     std::string location5;
//     float distance5;
//     float rating5;
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addVertex(std::string restaurantName, std::string category, std::string location, float rating, float distance);
    void addEdge(std::string restaurant1, std::string restaurant2);
    vertex *findVertex(std::string name);
    void displayEdges();
    void recommend();
    void buildEdges();
    void saveRestaurant(string restaurantName);
    void displayAllVertices();
    void displaySaved();
    void buildJSON(vector<vertex> tempRec);

  private:
    std::vector<vertex> vertices; //stores vertices

    std::vector<vertex*> savedRestaurants;
    
    void displayVertex(vertex *v);
    bool inEdges(vertex *v1, vertex *v2);
    bool inRecommendations(vertex *v, vector<vertex*> recommendations);
    void setWeights(vector<vertex*> recommendations);
    void sortRecommendations();
    float calcWeight(vertex *v);

};


BEGIN_CLASS_DESCRIPTOR(jsonVertex)
   CLASS_DESCRIPTOR_ENTRY(name)
   CLASS_DESCRIPTOR_ENTRY(category)
   CLASS_DESCRIPTOR_ENTRY(location)
   CLASS_DESCRIPTOR_ENTRY(distance)
   CLASS_DESCRIPTOR_ENTRY(rating)
END_CLASS_DESCRIPTOR()
