#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "finalProject.h"

bool catchAll(string saveName);

int main(int argc, char *argv[]){

	//CATCH ALL FUNCTION METHOD FOR SERVER

	// string argument;

	// for(int i = 1; i < argc; i++){
	// 	argument = argument + argv[i] + " ";
	// }

	// argument.erase(argument.end() - 1, argument.end());


	// if(catchAll(argument)){
	// 	cout << "Success" << endl;
	// }else{
	// 	cout << "Failed" << endl;
	// }



	// TERMINAL INTERFACE METHOD:

	Graph g0;

	ifstream inStream;

	for(int i = 1; i < argc; i++){
		inStream.open(argv[i]);

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
				getline(ss, name, '"');
				getline(ss, rating, '"');
				getline(ss, location, '"');
				// getline(ss, street, ',');
				// getline(ss, city, ',');
				// getline(ss, state, ',');
				// getline(ss, country, ',');
				//location = street + city + state + country;
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

	//read in previously saved data
	g0.loadData();

	//done building reference graph and edges. Start UI

	string choice = "0";
	while(stoi(choice) != 5){
		cout << "======Main Menu======" << endl;
		cout << "1. Save a new restaurant" << endl;
		cout << "2. Get recommendations" << endl;
		cout << "3. Show saved restaurants" << endl;
		cout << "4. Show all restaurants" << endl;
		cout << "5. Quit" << endl;

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
				g0.displaySaved();
				break;
			}
			case 4:{
				g0.displayAllVertices();
				break;
			}
			case 5:{
				g0.saveData();
				break;
			}
		}
	}




	return 0;
}


bool catchAll(string saveName){
	Graph g0;
	ifstream inStream;

	vector<string> files = {"American.csv", "Chinese.csv", "Indian.csv", "Italian.csv", "Mexican.csv", "Pizza.csv", "Sandwiches.csv"};

	for(int i = 0; i < files.size(); i++){
		inStream.open(files[i]);
		stringstream ss;
		string line;
		string name;
		string category;

		string location;

		string rating;
		string distance;

		if(inStream.is_open()){
			while(getline(inStream, line)){
				//cout << line << endl;
				ss << line;
				getline(ss, name, '"');
				getline(ss, rating, '"');
				getline(ss, location, '"');
	
				category = files[i];
				//category.erase (category.begin(), category.begin()+2);
				category.erase(category.end()-4, category.end());
				getline(ss, distance);

				g0.addVertex(name, category, location, stof(rating), stof(distance));

				ss.clear();
			}
			inStream.close();	


		}
	}
	g0.buildEdges();

	cout << g0.findVertex(saveName) << endl;

	g0.loadData();

	if(g0.findVertex(saveName)){
		g0.saveRestaurant(saveName);
	}else{
		return false;
	}

	g0.recommend();

	g0.saveData();

	return true;

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