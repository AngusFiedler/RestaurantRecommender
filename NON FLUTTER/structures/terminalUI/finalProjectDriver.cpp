#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

#include "finalProject.h"

bool catchAll(string saveName);

float haversine(float lon1, float lat1, float lon2, float lat2);

int main(int argc, char *argv[]){

	//CATCH ALL FUNCTION METHOD FOR SERVER

	// string argument;

	// for(int i = 1; i < argc; i++){
	// 	argument = argument + argv[i] + " ";
	// }

	// argument.erase(argument.end() - 1, argument.end());
	// //cout << argument << endl;

	// if(catchAll(argument)){
	// 	cout << "Success" << endl;
	// }else{
	// 	cout << "Failed" << endl;
	// }



	// TERMINAL INTERFACE METHOD:

	Graph g0;

	ifstream inStream;

	vector<string> files = {"allRestaurants.csv", "newRestaurants.csv"};

	for(int i = 0; i < files.size(); i++){
		inStream.open(files[i]);
		stringstream ss;
		string line;

		string name;
		string category;
		string rating;
		string location;
		string lat;
		string lng;
		float distance = 0;
		

		if(inStream.is_open()){
			while(getline(inStream, line)){
				//cout << line << endl;
				ss << line;
				getline(ss, name, '"');
				getline(ss, category, '"');
				getline(ss, rating, '"');
				getline(ss, location, '"');
				getline(ss, lat, '"');
				getline(ss, lng);
				//cout << lat << " " << lng << endl;
				distance = haversine(stod(lat), stod(lng), 40.005657, -105.264368);

				if(!g0.findVertex(name, location)){
					g0.addVertex(name, category, location, stod(rating), stod(lat), stod(lng), distance);
				}
				

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
	while(stoi(choice) != 6){
		cout << "======Main Menu======" << endl;
		cout << "1. Save a new restaurant" << endl;
		cout << "2. Get recommendations" << endl;
		cout << "3. Show saved restaurants" << endl;
		cout << "4. Remove a saved restaurant" << endl;
		cout << "5. Show all restaurants" << endl;
		cout << "6. Quit" << endl;

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
				string catSpec;
				cout << endl << "Category Specific? Y/n" << endl; 
				getline(cin, catSpec);
				if(catSpec == "y" || catSpec == "Y"){
					cout << "American, Chinese, Indian, Italian, Mexican, Pizza, Sandwiches" << endl;
					cout << "Enter category: ";
					getline(cin, catSpec);
					g0.recommend(catSpec);
				}else{
					g0.recommend();
				}
				cout << endl;
				break;
			}
			case 3:{
				g0.displaySaved();
				break;
			}
			case 4:{
				string name;
				cout << endl << "Enter the name of the restaurant: ";
				getline(cin, name);
				if(g0.findVertex(name)->saved){
					g0.removeSaved(name);
				}else{
					cout << "You have not saved this restaurant. No changes made" << endl;
				}
				break;
			}
			case 5:{
				g0.displayAllVertices();
				break;
			}
			case 6:{
				g0.saveData();
				break;
			}
		}
	}




	return 0;
}


float haversine(float lat1, float lon1, float lat2, float lon2){
	double pi = 3.141592653589793;

	lon1 = lon1*pi/180;
	lat1 = lat1*pi/180;
	lon2 = lon2*pi/180;
	lat2 = lat2*pi/180;

	double dlon = lon2 - lon1;
	double dlat = lat2 - lat1;

	double a = pow(sin(dlat/2),2) + cos(lat1) * cos(lat2) * pow(sin(dlon/2),2);
	double c = 2*asin(sqrt(a));
	double r = 3956;
	return (float) c*r;
}


bool catchAll(string saveName){

	Graph g0;
	ifstream inStream;

	//vector<string> files = {"/home/angusfiedler/deploy/RestCSV/American.csv", "/home/angusfiedler/deploy/RestCSV/Chinese.csv", "/home/angusfiedler/deploy/RestCSV/Indian.csv", "/home/angusfiedler/deploy/RestCSV/Italian.csv", "/home/angusfiedler/deploy/RestCSV/Mexican.csv", "/home/angusfiedler/deploy/RestCSV/Pizza.csv", "/home/angusfiedler/deploy/RestCSV/Sandwiches.csv"};
	vector<string> files = {"allRestaurants.csv", "newRestaurants.csv"};

	for(int i = 0; i < files.size(); i++){
		inStream.open(files[i]);
		stringstream ss;
		string line;

		string name;
		string category;
		string rating;
		string location;
		string lat;
		string lng;
		float distance = 0;
		

		if(inStream.is_open()){
			while(getline(inStream, line)){
				//cout << line << endl;
				ss << line;
				getline(ss, name, '"');
				getline(ss, category, '"');
				getline(ss, rating, '"');
				getline(ss, location, '"');
				getline(ss, lat, '"');
				getline(ss, lng);
				//cout << lat << " " << lng << endl;
				distance = haversine(stod(lat), stod(lng), 40.005657, -105.264368);

				if(!g0.findVertex(name, location)){
					g0.addVertex(name, category, location, stod(rating), stod(lat), stod(lng), distance);
				}
				

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