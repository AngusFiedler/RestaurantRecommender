#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#include "finalProject.h"

bool operator<(const Edge& e1, const Edge& e2){return e1.v->rating > e2.v->rating;}

Graph::Graph(){

}

Graph::~Graph(){

}

void Graph::addVertex(string restaurantName, string category, string location, float rating, float distance){
	vertex v1;
	v1.name = restaurantName;
	v1.category = category;
	v1.location = location;
	v1.distance = distance;
	v1.rating = rating;
	v1.saved = false;
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

	sortEdges();
}

void Graph::sortEdges(){
	for(int i = 0; i < vertices.size(); i++)
		sort(vertices[i].Edges.begin(), vertices[i].Edges.end());
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

	sortEdges();
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
		if(vertices[i].name == name){
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
			cout << v->Edges[i].v->name << endl;
			DFT_recursive(v->Edges[i].v);
		}
	}
}

void Graph::BFT_traversal(vertex *v){
	cout << v->name << endl;
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
				cout << n->Edges[i].v->name << endl;
			}
		}
	}
}

void Graph::DFT_traversal(vertex *v){
	cout << v->name << endl;
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
	cout << v->name << endl;
	cout << "	Category: " << v->category << endl;
	cout << "	Location: " << v->location<< endl;
	cout << "	Distance: " << v->distance << " miles" << endl;
	cout << "	Rating: " << v->rating << endl;
}