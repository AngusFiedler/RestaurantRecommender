#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#include "finalProject.h"

Graph::Graph(){

}

Graph::~Graph(){

}

void Graph::addVertex(string restaurantName, string category, string location, float rating){
	vertex v1;
	v1.restaurant.name = restaurantName;
	v1.restaurant.category = category;
	v1.restaurant.location = location;
	v1.restaurant.rating = rating;
	vertices.push_back(v1);
}

void Graph::addEdge(string restaurant1, string restaurant2){
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].restaurant.name == restaurant1){
			for(int j = 0; j < vertices.size(); j++){
				if(vertices[j].restaurant.name == restaurant2 && j!=i){
					Edge e0;
					e0.v = &vertices[j];
					vertices[i].Edges.push_back(e0);
					//add vertex in other direction
					Edge e1;
					e1.v = &vertices[i];
					vertices[j].Edges.push_back(e1);
				}
			}
		}
	}
}

void Graph::displayEdges(){
	for(int i = 0; i < vertices.size(); i++){
		cout << vertices[i].restaurant.name << "-->";
		for(int j = 0; j < vertices[i].Edges.size(); j++){
			if(j < vertices[i].Edges.size()-1){
				cout << vertices[i].Edges[j].v->restaurant.name << "-->";
			}else{
				cout << vertices[i].Edges[j].v->restaurant.name << endl;
			}
		}
		cout << endl;
	}
}

void Graph::setAllVerticesUnvisited(){
	for(int i = 0; i < vertices.size(); i++){
		vertices[i].visited = false;
	}
}

void Graph::printDFT(){
	setAllVerticesUnvisited();
	for(int i = 0; i < vertices.size(); i++){
		if(!vertices[i].visited)
			DFT_traversal(&vertices[i]);
	}
}

void Graph::printBFT(){
	setAllVerticesUnvisited();
	for(int i = 0; i < vertices.size(); i++){
		if(!vertices[i].visited)
			BFT_traversal(&vertices[i]);
	}
}


vertex* Graph::findVertex(string name){
	vertex *found;
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].restaurant.name == name){
			found = &vertices[i];
			break;
		}
	}

	return found;
}

void DFT_recursive(vertex *v){
	v->visited = true;
	for(int i = 0; i < v->Edges.size(); i++){
		if(!v->Edges[i].v->visited){
			cout << v->Edges[i].v->restaurant.name << endl;
			DFT_recursive(v->Edges[i].v);
		}
	}
}

void Graph::BFT_traversal(vertex *v){
	cout << v->restaurant.name << endl;
	v->visited = true;

	queue<vertex*> q;
	q.push(v);

	vertex *n;

	while(!q.empty()){
		n = q.front();
		q.pop();

		for(int i = 0; i < n->Edges.size(); i++){
			if(!n->Edges[i].v->visited){
				n->Edges[i].v->visited = true;
				q.push(n->Edges[i].v);
				cout << n->Edges[i].v->restaurant.name << endl;
			}
		}
	}
}

void Graph::DFT_traversal(vertex *v){
	cout << v->restaurant.name << endl;
	DFT_recursive(v);
}


void Graph::recommend(string restaurantName){
	vertex *found = findVertex(restaurantName);

	if(found != nullptr){
		if(found->Edges.size() >= 5){
			cout << "Top 5 related restaurants for " << restaurantName << ":" << endl;
			for(int i = 0; i < 5; i++){
				displayVertex(found->Edges[i].v);
			}
		}else{
			cout << "Top " << found->Edges.size() << " related restaurants for " << restaurantName << ":" << endl;
			for(int i = 0; i < found->Edges.size(); i++){
				displayVertex(found->Edges[i].v);
			}
		}

		
	}
}


void Graph::displayVertex(vertex *v){
	cout << v->restaurant.name << endl;
	cout << "	Category: " << v->restaurant.category << endl;
	cout << "	Location: " << v->restaurant.location<< endl;
	cout << "	Rating: " << v->restaurant.rating << endl;
}