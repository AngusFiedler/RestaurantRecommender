#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "finalProject.h"

int main(int argc, char *argv[]){

	//User user0;

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

		//done building reference graph and edges. Start UI

		string choice = "0";
		while(stoi(choice) != 3){
			cout << "======Main Menu======" << endl;
			cout << "1. Save a new restaurant" << endl;
			cout << "2. Get recommendations" << endl;
			cout << "3. Quit" << endl;

			getline(cin, choice);

			switch(stoi(choice)){
				case 1:{
					string name;
					cout << endl << "Enter the name of the restaurant: ";
					getline(cin, name);
					if(!g0.findVertex(name)){
						cout << endl << "Sorry, restaurant is not in directory yet. Please try another restaurant" << endl << endl;
					}else{
						g0.saveRestaurant(name);
						cout << endl << "Restaurant saved!!" << endl << endl;
					}
					break;
				}
				case 2:{
					cout <<endl;
					g0.recommend();
					cout << endl;
					break;
				}
				case 3:{
					cout << "Goodbye!" << endl;
					break;
				}
			}
		}


		







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