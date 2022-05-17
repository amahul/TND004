/*********************************************
 * file:	~\code4a\digraph.cpp              *
 * remark: implementation of directed graphs  *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <queue>
#include <limits>

#include "digraph.h"

 // Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

const int inf = std::numeric_limits<int>::max();
// -- CONSTRUCTORS

Digraph::Digraph(int n)
	: table(size_t(n) + 1)
	, size{ n }
	, n_edges{ 0 }
	, dist(size_t(n) + 1)
	, path(size_t(n) + 1)
	, done(size_t(n) + 1) {
	assert(n >= 1);

	// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<Edge>& V, int n) : Digraph{ n } {
	for (auto e : V) {
		insertEdge(e);
	}
}

// -- MEMBER FUNCTIONS

// insert directed edge e = (u, v, w)
// update weight w if edge (u, v) is present
void Digraph::insertEdge(const Edge& e) {
	assert(e.head >= 1 && e.head <= size);
	assert(e.tail >= 1 && e.tail <= size);

	// Check if edge e already exists
	if (auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
		[e](const Edge& ed) { return e.links_same_nodes(ed); });
		it == end(table[e.head])) {
		table[e.head].push_back(e);  // insert new edge e
		++n_edges;
	}
	else {
		it->weight = e.weight;  // update the weight
	}
}

// remove directed edge e
void Digraph::removeEdge(const Edge& e) {
	assert(e.head >= 1 && e.head <= size);
	assert(e.tail >= 1 && e.tail <= size);

	auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
		[e](const Edge& ed) { return e.links_same_nodes(ed); });

	assert(it != end(table[e.head]));
	table[e.head].erase(it);
	--n_edges;
}

// construct unweighted single source shortest path-tree for start vertex s
void Digraph::uwsssp(int s) const {
	assert(s >= 1 && s <= size);

	// *** IMPLEMENTED ***
	std::queue<int> Q;

	// O(n)
	// Loop through all slots and set initial value
	for (int i = 1; i <= size; i++) {
		dist[i] = inf; // record distance
		path[i] = 0; // record path
	}

	dist[s] = 0; // Distance for start node
	// Inserts a new element at the rear of the queue
	Q.push(s); // Start node in queue

	// O(n+m)
	while (!Q.empty()) {
		// Removes the front element of the queue and returns it
		int v = Q.front(); // Returns first element of queue
		Q.pop(); // Remove first element

		// Loop through every vertex u adjacent to v (intilliggande noder till v)
		for (auto it = table[v].begin(); it != table[v].end(); ++it) {
			int u = it->tail; // u is a vertex adjacent to v

			if (dist[u] == inf) { //if dist[u] is inf it hasn't been visited yet			
				dist[u] = dist[v] + 1;
				path[u] = v;
				Q.push(u);
			}
		}
	}
}

// construct positive weighted single source shortest path-tree for start vertex s
// Dijktra’s algorithm
void Digraph::pwsssp(int s) const {
	assert(s >= 1 && s <= size);

	// *** IMPLEMENTED ***
	// O(n)
	// Loop through all slots and set initial value
	for (int i = 1; i <= size; i++) {
		dist[i] = inf; // record distance
		path[i] = 0; // record path
		done[i] = false;
	}

	dist[s] = 0;
	done[s] = true;
	int v = s;

	while (true) {
		// Loop through every vertex u adjacent to v (intilliggande noder till v)
		for (auto it = table[v].begin(); it != table[v].end(); ++it) {
			int u = it->tail; // u is a vertex adjacent to v
			if (done[u] == false && dist[u] > dist[v] + it->weight) { //if dist[u] is inf it hasn't been visited yet
				dist[u] = dist[v] + it->weight;
				path[u] = v;
			}
		}

		int distMin = inf;

		// Loop through all vertices
		for (int i = 1; i <= size; i++) {
			// Check if vertice is not visited and distance is smaller than previous smallest
			if (!done[i] && dist[i] < distMin) {
				// Update smallest distance
				distMin = dist[i];
				v = i;
			}
		}

		if (distMin == inf) break; //exit the loop if we haven't found anything smaller than inf
		done[v] = true;
	}

}

// print graph
void Digraph::printGraph() const {
	std::cout << "------------------------------------------------------------------\n";
	std::cout << "vertex  adjacency list                  \n";
	std::cout << "------------------------------------------------------------------\n";

	for (int v = 1; v <= size; ++v) {
		std::cout << std::setw(4) << v << " : ";
		for (auto it = table[v].begin(); it != table[v].end(); ++it) {
			std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight << ") ";
		}
		std::cout << "\n";
	}
	std::cout << "------------------------------------------------------------------\n";
}

// print shortest path tree for s
void Digraph::printTree() const {
	std::cout << "----------------------\n";
	std::cout << "vertex    dist    path\n";
	std::cout << "----------------------\n";

	for (int v = 1; v <= size; ++v) {
		std::cout << std::setw(4) << v << " :" << std::setw(8)
			<< ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]) << std::setw(8)
			<< path[v] << "\n";
	}
	std::cout << "----------------------\n";
}

// print shortest path from s to t and the corresponding path length
// Hint: consider using recursion
void Digraph::printPath(int t) const {
	assert(t >= 1 && t <= size);

	// Call printHelp for source
	printHelp(t);

	// Print distance in end
	std::cout << "(" << dist[t] << ")";
}


void Digraph::printHelp(int t) const {
	// Print and return if we are at source
	if (path[t] == 0) {
		std::cout << " " << t << " ";

		return;
	}

	// Recursive call
	printHelp(path[t]);
	// Print value
	std::cout << " " << t << " ";

}
