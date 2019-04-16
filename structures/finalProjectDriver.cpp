#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "finalProject.h"

int main(int argc, char *argv[]){

	Graph g0;

	ifstream inStream;
	inStream.open(argv[1]);

	stringstream ss;
	string line;
	string name;
	string category;
	string location;
	string rating;
	string distance;

	if(inStream.is_open()){
		while(getline(inStream, line)){
			ss << line;
			getline(ss, name, ',');
			getline(ss, category, ',');
			getline(ss, location, ',');
			getline(ss, rating, ',');
			getline(ss, distance);

			//cout << name << category << location << rating << distance << endl;

			g0.addVertex(name, category, location, stof(rating), stof(distance));

			ss.clear();
		}


		//done reading in restaurants. build edges based on category
		g0.buildEdges();

		//g0.displayEdges();

		//recommend a restaurant, sorted by restaurant rating
		g0.recommend("Oak");





	}else{
		cout << "Error opening data file" << endl;
	}


	return 0;
}






// g0.addVertex("McDonalds", "American Fast Food", "Boulder", 4.5);
	// g0.addVertex("Wendys", "American Fast Food", "Broomfield", 4.8);
	// g0.addVertex("Taco Bell", "Mexican Fast Food", "Boulder", 3.5);
	// g0.addVertex("Chipotle", "Mexican", "Denver", 5.0);
	// g0.addVertex("Qdoba", "Mexican", "Estes Park", 4.9);
	// g0.addVertex("Smashburger", "American", "Westminister", 4.7);
	// g0.addVertex("Five Guys", "American", "Boulder", 5.0);

	// g0.addEdge("McDonalds", "Wendys");
	// g0.addEdge("Taco Bell", "Chipotle");
	// g0.addEdge("Taco Bell", "Qdoba");
	// g0.addEdge("Qdoba", "Chipotle");
	// g0.addEdge("Smashburger", "McDonalds");
	// g0.addEdge("Smashburger", "Wendys");
	// g0.addEdge("Five Guys", "Smashburger");
	// g0.addEdge("Five Guys", "McDonalds");
	// g0.addEdge("Five Guys", "Wendys");

	// g0.recommend("McDonalds");
	// g0.recommend("Chipotle");