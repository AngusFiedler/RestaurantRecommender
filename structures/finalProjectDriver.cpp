#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "finalProject.h"

int main(){

	Graph g0;


	g0.addVertex("McDonalds", "American Fast Food", "Boulder", 4.5);
	g0.addVertex("Wendys", "American Fast Food", "Broomfield", 4.8);
	g0.addVertex("Taco Bell", "Mexican Fast Food", "Boulder", 3.5);
	g0.addVertex("Chipotle", "Mexican", "Denver", 5.0);
	g0.addVertex("Qdoba", "Mexican", "Estes Park", 4.9);
	g0.addVertex("Smashburger", "American", "Westminister", 4.7);
	g0.addVertex("Five Guys", "American", "Boulder", 5.0);

	g0.addEdge("McDonalds", "Wendys");
	g0.addEdge("Taco Bell", "Chipotle");
	g0.addEdge("Taco Bell", "Qdoba");
	g0.addEdge("Qdoba", "Chipotle");
	g0.addEdge("Smashburger", "McDonalds");
	g0.addEdge("Smashburger", "Wendys");
	g0.addEdge("Five Guys", "Smashburger");
	g0.addEdge("Five Guys", "McDonalds");
	g0.addEdge("Five Guys", "Wendys");

	g0.recommend("McDonalds");
	g0.recommend("Chipotle");
	//g0.displayEdges();


	return 0;
}