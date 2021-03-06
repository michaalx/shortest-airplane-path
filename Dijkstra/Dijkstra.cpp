/*
The implementation of Dijkstra algorithm
using Standard Template Library, priority_queue as ADT.
Adding more vertices in main() function than defined
causes crash.
Author: Michal Stankevic, SE 3.
*/

#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>
#include <tuple>
#include <climits>
#include <cstdio>
#include <iostream>

using namespace std;

typedef tuple<int, int, int> triple;

class Graph
{
	int nrOfVertices;
	vector<string> cities;
	list<triple> *adjacencyList;

public:
	Graph(int nrOfVertices);
	void addEdge(int source, int destination, int finalTime, int departure);
	void shortestPath(int destination, int destinationVertex);
	void inputEdge(string sourceCity, string destinationCity, int hours, int minutes, int duration);
	void printPath(vector<int> &previousVertex, vector<int> &finalTime, int destination);
};

Graph::Graph(int nrOfVertices)
{
	this->nrOfVertices = nrOfVertices;
	adjacencyList = new list<triple>[nrOfVertices];
}

void Graph::addEdge(int source, int destination, int finalTime, int departure)
{
	adjacencyList[source].push_back(make_tuple(destination, finalTime, departure));
}

void Graph::printPath(vector<int> &previousVertex, vector<int> &finalTime, int destination)
{
	if (finalTime[destination] == -1) {
		cout << "Path between " << cities[0] << " and " << cities[destination] << " does not exist. " << endl;
	}
	if (previousVertex[destination] == -1) {
		cout << cities[destination] << " ";
		return;
	}
	printPath(previousVertex, finalTime, previousVertex[destination]);
	cout << cities[destination] << " ";
}

void Graph::shortestPath(int sourceVertex, int destinationVertex)   //Dijkstra algorithm.
{
	priority_queue <triple, vector<triple>, greater<triple> > priorityQueue;
	vector<int> finalTime(nrOfVertices, INT_MAX);
	vector<int> previousVertex(nrOfVertices);
	priorityQueue.push(make_tuple(0, sourceVertex, INT_MAX)); //make_tuple(ultimateTime,destination,departure)
	finalTime[sourceVertex] = 0;
	previousVertex[sourceVertex] = -1;
	while (!priorityQueue.empty()) {

		int vertex = get<1>(priorityQueue.top());   //extract minimum distance vertex from PQ
		priorityQueue.pop();
		list< triple >::iterator i; //iterate through all vertices adjacent to vertex
		for (i = adjacencyList[vertex].begin(); i != adjacencyList[vertex].end(); ++i) {

			int nextVertex = get<0>((*i));
			int timeCandidate = get<1>((*i));	//temporary
			int departure = get<2>(*i);
			if ((finalTime[vertex] <= departure) && (finalTime[nextVertex] > timeCandidate)) {
				finalTime[nextVertex] = timeCandidate;
				priorityQueue.push(make_tuple(finalTime[nextVertex], nextVertex, departure));
				previousVertex[nextVertex] = vertex;
			}
		}
	}

	printPath(previousVertex, finalTime, destinationVertex);
	std::cout << finalTime[destinationVertex] / 60 << ":" << finalTime[destinationVertex] % 60 << endl;
	getchar();
}

void Graph::inputEdge(string sourceCity, string destinationCity, int hours, int minutes, int duration)
{
	int sourceAsIndex, destinationAsIndex;
	int finalTime;
	int convertedDeparture;
	if (find(cities.begin(), cities.end(), sourceCity) != cities.end()) {

		sourceAsIndex = distance(cities.begin(), find(cities.begin(), cities.end(), sourceCity));
	}
	else {
		cities.push_back(sourceCity);
		sourceAsIndex = cities.size() - 1;
	}
	if (find(cities.begin(), cities.end(), destinationCity) != cities.end()) {
		destinationAsIndex = distance(cities.begin(), find(cities.begin(), cities.end(), destinationCity));
	}
	else {
		cities.push_back(destinationCity);
		destinationAsIndex = cities.size() - 1;
	}
	convertedDeparture = hours * 60 + minutes;
	finalTime = convertedDeparture + duration;
	addEdge(sourceAsIndex, destinationAsIndex, finalTime, convertedDeparture);
	return;
}

int main()
{
	// Use case.

	int nrOfVertices = 7;
	Graph g(nrOfVertices);

	g.inputEdge("Vilnius", "Kaunas", 14, 10, 30);
	g.inputEdge("Kaunas", "Palanga", 15, 10, 45);
	g.inputEdge("Vilnius", "Siauliai", 14, 10, 45);
	g.inputEdge("Siauliai", "Palanga", 15, 55, 35);
	g.inputEdge("Vilnius", "Alytus", 16, 10, 20);
	g.inputEdge("Alytus", "Kaunas", 17, 10, 50);
	g.inputEdge("Palanga", "Riga", 15, 15, 15);
	g.inputEdge("Klaipeda", "Riga", 15, 15, 15);
	g.shortestPath(0, 2);

	
	return 0;
}
