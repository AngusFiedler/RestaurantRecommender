#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#include "finalProject.h"


bool operator<(const vertex& v1, const vertex& v2){return v1.weight > v2.weight;}

Graph::Graph(){

}

Graph::~Graph(){

}

float calcWeight(vertex *v){

}

void Graph::addVertex(string restaurantName, string category, string location, float rating, float distance){
	vertex v1;
	v1.name = restaurantName;
	v1.category = category;
	v1.location = location;
	v1.distance = distance;
	v1.rating = rating;
	v1.saved = false;
	v1.count = 1;
	vertices.push_back(v1);
	
}

void Graph::addEdge(string restaurant1, string restaurant2){
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].name == restaurant1){
			for(int j = 0; j < vertices.size(); j++){
				if(vertices[j].name == restaurant2 && j!=i){
					Edge e0;
					e0.v = &vertices[j];
					//e0.distance = distance;
					vertices[i].Edges.push_back(e0);
					//add vertex in other direction
					Edge e1;
					e1.v = &vertices[i];
					//e1.distance = distance;
					vertices[j].Edges.push_back(e1);
				}
			}
		}
	}


}


bool Graph::inEdges(vertex *v1, vertex *v2){
	for(int i = 0; i < v1->Edges.size(); i++){
		if(v2->name == v1->Edges[i].v->name)
			return true;
	}

	return false;
}

void Graph::buildEdges(){
	for(int i = 0; i < vertices.size(); i++){
		string category = vertices[i].category;
		
		for(int j = 0; j < vertices.size(); j++){
			if(vertices[j].category == category && j!=i && !inEdges(&vertices[i], &vertices[j])){
				Edge e0;
				e0.v = &vertices[j];
				//e0.distance = distance;
				vertices[i].Edges.push_back(e0);
				//add vertex in other direction
				Edge e1;
				e1.v = &vertices[i];
				//e1.distance = distance;
				vertices[j].Edges.push_back(e1);
			}
		}

	}

}


void Graph::displayEdges(){
	for(int i = 0; i < vertices.size(); i++){
		cout << vertices[i].name << "-->";
		for(int j = 0; j < vertices[i].Edges.size(); j++){
			if(j < vertices[i].Edges.size()-1){
				cout << vertices[i].Edges[j].v->name << "-->";
			}else{
				cout << vertices[i].Edges[j].v->name << endl;
			}
		}
		cout << endl;
	}
}

// void Graph::setAllVerticesUnvisited(){
// 	for(int i = 0; i < vertices.size(); i++){
// 		vertices[i].visited = false;
// 	}
// }

// void Graph::printDFT(){
// 	setAllVerticesUnvisited();
// 	for(int i = 0; i < vertices.size(); i++){
// 		if(!vertices[i].visited)
// 			DFT_traversal(&vertices[i]);
// 	}
// }

// void Graph::printBFT(){
// 	setAllVerticesUnvisited();
// 	for(int i = 0; i < vertices.size(); i++){
// 		if(!vertices[i].visited)
// 			BFT_traversal(&vertices[i]);
// 	}
// }


vertex* Graph::findVertex(string name){
	vertex *found = nullptr;
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].name == name){
			found = &vertices[i];
			break;
		}
	}

	return found;
}

// void DFT_recursive(vertex *v){
// 	v->visited = true;
// 	for(int i = 0; i < v->Edges.size(); i++){
// 		if(!v->Edges[i].v->visited){
// 			cout << v->Edges[i].v->name << endl;
// 			DFT_recursive(v->Edges[i].v);
// 		}
// 	}
// }

// void Graph::BFT_traversal(vertex *v){
// 	cout << v->name << endl;
// 	v->visited = true;

// 	queue<vertex*> q;
// 	q.push(v);

// 	vertex *n;

// 	while(!q.empty()){
// 		n = q.front();
// 		q.pop();

// 		for(int i = 0; i < n->Edges.size(); i++){
// 			if(!n->Edges[i].v->visited){
// 				n->Edges[i].v->visited = true;
// 				q.push(n->Edges[i].v);
// 				cout << n->Edges[i].v->name << endl;
// 			}
// 		}
// 	}
// }

// void Graph::DFT_traversal(vertex *v){
// 	cout << v->name << endl;
// 	DFT_recursive(v);
// }

void Graph::sortRecommendations(){
		
}

void Graph::setWeights(vector<vertex*> recommendations){
	float distance;
    float rating;
    int count;
    float weight;
	for(int i = 0; i < recommendations.size(); i++){
		distance = recommendations[i]->distance;
		rating = recommendations[i]->rating;
		count = recommendations[i]->count;
		weight = 3*count + 3*rating - 2*distance;
		recommendations[i]->weight = weight;
	}
}


bool Graph::inRecommendations(vertex *v, vector<vertex*> recommendations){
	for(int i = 0; i < recommendations.size(); i++){
		if(recommendations[i]->name == v->name)
			return true;
	}

	return false;
}


void Graph::recommend(){

	vector<vertex*> recommendations;

	if(savedRestaurants.size() == 0)
		return;

	for(int i = 0; i < savedRestaurants.size(); i++){
		
		for(int j = 0; j < savedRestaurants[i]->Edges.size(); j++){
			if(!inRecommendations(savedRestaurants[i]->Edges[j].v, recommendations) && !savedRestaurants[i]->Edges[j].v->saved){
				recommendations.push_back(savedRestaurants[i]->Edges[j].v);
			}else{
				savedRestaurants[i]->Edges[j].v->count++;
			}
		}
	}


	setWeights(recommendations);

	vector<vertex> tempRec;

	for(int i = 0; i < recommendations.size(); i++){
		tempRec.push_back(*recommendations[i]);
	}

	sort(tempRec.begin(), tempRec.end());

	buildJSON(tempRec);


	if(recommendations.size() >= 5){
		cout << "Top 5 related restaurants: " << endl;
		for(int i = 0; i < 5; i++){
			displayVertex(&tempRec[i]);
			}
	}else{
		cout << "Top " << recommendations.size() << " related restaurants:" << endl;
		for(int i = 0; i < recommendations.size(); i++){
			displayVertex(&tempRec[i]);
		}
	}

	// vertex *found = findVertex(restaurantName);

	// if(found != nullptr){
	// 	if(found->Edges.size() >= 5){
	// 		cout << "Top 5 related restaurants for " << restaurantName << ":" << endl;
	// 		for(int i = 0; i < 5; i++){
	// 			displayVertex(found->Edges[i].v);
	// 		}
	// 	}else{
	// 		cout << "Top " << found->Edges.size() << " related restaurants for " << restaurantName << ":" << endl;
	// 		for(int i = 0; i < found->Edges.size(); i++){
	// 			displayVertex(found->Edges[i].v);
	// 		}
	// 	}

		
	// }
}

void Graph::saveRestaurant(string restaurantName){
	bool found = false;
	for(int i = 0; i < savedRestaurants.size(); i++){
		if(savedRestaurants[i]->name == restaurantName){
			found = true;
			savedRestaurants[i]->count++;
		}
	}

	if(!found){
		vertex *v = findVertex(restaurantName);
		savedRestaurants.push_back(v);
		v->saved = true;
		v->count++;
	}
}


void Graph::displayVertex(vertex *v){
	cout << v->name << endl;
	cout << "	Category: " << v->category << endl;
	cout << "	Location: " << v->location<< endl;
	cout << "	Distance: " << v->distance << " miles" << endl;
	cout << "	Rating: " << v->rating << endl;
	cout << "	Count: " << v->count << endl;
	cout << "	Weight: " << v->weight << endl;
}

void Graph::displayAllVertices(){
	for(int i = 0; i < vertices.size(); i++){
		displayVertex(&vertices[i]);
	}
}

void Graph::displaySaved(){
	for(int i = 0; i < savedRestaurants.size(); i++){
		displayVertex(savedRestaurants[i]);
	}
}


void Graph::buildJSON(vector<vertex> tempRec){
	vector<jsonVertex> outs(5);

	for(int i = 0; i < 5; i++){
		outs[i].name = tempRec[i].name;
		outs[i].category = tempRec[i].category;
		outs[i].location = tempRec[i].location;
		outs[i].distance = tempRec[i].distance;
		outs[i].rating = tempRec[i].rating;
		outs[i].category = tempRec[i].category;
	}

	//FILE STREAM METHOD

	// ofstream writeFile1("1.json");
	// WriteJSON(writeFile1, outs[0]);

	// ofstream writeFile2("2.json");
	// WriteJSON(writeFile2, outs[1]);

	// ofstream writeFile3("3.json");
	// WriteJSON(writeFile3, outs[2]);

	// ofstream writeFile4("4.json");
	// WriteJSON(writeFile4, outs[3]);

	// ofstream writeFile5("5.json");
	// WriteJSON(writeFile5, outs[4]);


	//STRING VARIABLE METHOD:

	string rec1 = ToJSON(outs[0]);
	string rec2 = ToJSON(outs[1]);
	string rec3 = ToJSON(outs[2]);
	string rec4 = ToJSON(outs[3]);
	string rec5 = ToJSON(outs[4]);


}