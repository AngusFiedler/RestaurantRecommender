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
	//cout << argc << endl;

	for(int i = 1; i < argc; i++){
		//cout << argv[i] << endl;
		inStream.open(argv[i]);

		stringstream ss;
		string line;
		string name;
		string category;

		string location;
		string street;
		string city;
		string state;
		string country;

		string rating;
		string distance;

		if(inStream.is_open()){
			while(getline(inStream, line)){
				ss << line;
				getline(ss, name, ',');
				getline(ss, rating, ',');
				getline(ss, street, ',');
				getline(ss, city, ',');
				getline(ss, state, ',');
				getline(ss, country, ',');
				location = street + city + state + country;
				category = argv[i];
				category.erase (category.begin(), category.begin()+2);
				category.erase(category.end()-4, category.end());
				getline(ss, distance);
			
				//cout << name << category << location << rating << distance << endl;
				//cout << i << endl;

				g0.addVertex(name, category, location, stof(rating), stof(distance));

				ss.clear();
			}
			inStream.close();	


		}else{
			cout << "Error opening data file" << endl;
		}
	}




	//done reading in restaurants. build edges based on category
	g0.buildEdges();

	//done building reference graph and edges. Start UI

	string choice = "0";
	while(stoi(choice) != 4){
		cout << "======Main Menu======" << endl;
		cout << "1. Save a new restaurant" << endl;
		cout << "2. Get recommendations" << endl;
		cout << "3. Show all Restaurants" << endl;
		cout << "4. Quit" << endl;

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
				g0.displayAllVertices();
				break;
			}
			case 4:{
				break;
			}
		}
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