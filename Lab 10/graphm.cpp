#include "graphm.h"
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#define UNVISITED -1;

#include <iostream>
using namespace std;

int GraphM::n() { return numVertex; }

int GraphM::e() { return numEdge; }

GraphM::GraphM(){}

GraphM::GraphM(int numVert){ Init(numVert); }

GraphM::~GraphM(){ delete [] mark; delete [] edges; }

void GraphM::Init(int n){
	int i;
	numVertex = n;
	numEdge = 0; 

	int arraySize = ((n - 1) * (n - 2))/2 + (n - 2);
	edges = new int[arraySize + 1];
	mark = new int[numVertex];

	for (i = 0; i < numVertex; i++)
		mark[i] = UNVISITED;

	for (i = 0; i < arraySize; i++) 
		edges[i] = 0;
}

int GraphM::first(int v){ 
	for (int i = 0; i < numVertex; i++)
		if (edges[calculate_edge(v, i)] != 0) return i;
	return numVertex;
};

int GraphM::next(int v, int w){ 
	for(int i = w + 1; i < numVertex; i++)
		if (edges[calculate_edge(v, i)] != 0) return i;
	return numVertex;
};

void GraphM::setEdge(int v1, int v2, int wght){
	if (edges[calculate_edge(v1, v2)] == 0) numEdge++;
	edges[calculate_edge(v1, v2)] = wght;
};

void GraphM::delEdge(int v1, int v2){
	if (edges[calculate_edge(v1, v2)] != 0) numEdge--;
	edges[calculate_edge(v1, v2)] = 0;
}

bool GraphM::isEdge(int i, int j){ 
	return edges[calculate_edge(i, j)] != 0; 
}

int GraphM::weight(int v1, int v2){ 
	return edges[calculate_edge(v1, v2)]; 
}

int GraphM::getMark(int v){ return mark[v]; }

void GraphM::setMark(int v, int val){ mark[v] = val; }

int GraphM::calculate_edge(int v1, int v2){
	if (v1 < v2) return calculate_edge(v2, v1);
	return ((v1 * (v1 - 1)) / 2) + v2;
}

void GraphM::viewGraph(){
	for (int i = 0; i < n(); i++) {
		for (int w = next(i, i); w < n(); w = next(i,w)) {
			cout << i << " - " << w << ": ";
			cout << weight(i, w) << endl;
		}
	}
}

Graph* read_graph(string filename) {
	/* 
	 * Reads in a csv file in the format of
	 * vertex 1, vertex2, weight. From there
	 * it parses the file by getting each 
	 * required element for the call to setEdge
	 * when it has all the values required, it will 
	 * then push temp to the vector then the 
	 * vector is later used to create the graph
	 */
	ifstream input_file(filename);
	string part;
	vector<GraphInfo> points;
	GraphInfo temp;
	int v1, v2, wt, fstComma, scdComma;

	fstComma = scdComma = 0;
	while(getline(input_file, part)){
		// Parse the string for commas
		for(int i = 0; i < part.length(); i++){
			if (part[i] == ',' && fstComma == 0){
				fstComma = i;
			}
			else if (part[i] == ',') {
				scdComma = i;
			}
		}

		// Split the string at the commas and cast to integers
		v1 = stoi(part.substr(0, fstComma));
		v2 = stoi(part.substr(fstComma + 1, scdComma - 2));
		wt = stoi(part.substr(scdComma + 1, part.length() - 1));

		// Push temp onto the vector to save the 
		// point in the graph so it can be added
		temp.v1 = v1; 
		temp.v2 = v2; 
		temp.wt = wt;
		points.push_back(temp);
	}

	// Get the vertice count
	vector<int> vertices;
	bool foundV1, foundV2;
	for(int i = 0; i < points.size(); i++){
		foundV1 = false;
		foundV2 = false;
		v1 = points[i].v1;
		v2 = points[i].v2;
		for(int j = 0; j < vertices.size(); j++){
			if(v1 == vertices[j]){
				foundV1 = true;
			}
			if(v2 == vertices[j]){
				foundV2 = true;
			}
		}
		if (!foundV1){
			vertices.push_back(v1);
		}
		if (!foundV2){
			vertices.push_back(v2);
		}
	}

	GraphM *new_graph = new GraphM(vertices.size());
	for(int i = 0; i < points.size(); i++){
		new_graph->setEdge(points[i].v1, points[i].v2, points[i].wt);
	}
	return new_graph;
}  

bool write_graph(Graph *g, string filename) {
	/*
	 * I could not figure out how to go from
	 * a single edge index back to both vertices
	 * so the output and input csv files are 
	 * different. This one has the format of
	 * edge index, weight. The data is derived
	 * from the edges area and the related
	 * weights stored at each index.
	 */
	ofstream output_file;
	output_file.open(filename);
	int vertices = g->n();
	int edges = g->e();

	int size = g->n();
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (g->isEdge(i,j)) {
                output_file << i << ',' << j << ',' << g->weight(i,j) << '\n';
            }
        }
    }

	output_file.close();
	return true;
} 
