/*********************************************
 * file:	~\code4b\graph.h                  *
 * remark:implementation of undirected graphs *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>  //assert

#include "graph.h"
#include "heap.h"
#include "dsets.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS
const int inf = std::numeric_limits<int>::max();

// Create a graph with n vertices and no vertices
Graph::Graph(int n) : table(size_t(n) + 1), size{n}, n_edges{0} {
    assert(n >= 1);
}

Graph::Graph(const std::vector<Edge> &V, int n) : Graph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge e
// update weight if edge e is present
void Graph::insertEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edge_insertion = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        if (auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                                   [e1](const Edge &ed) { return e1.links_same_nodes(ed); });
            it == end(T[e1.head])) {
            T[e1.head].push_back(e1);  // insert new edge e
            ++n;                       // increment the counter of edges
        } else {
            it->weight = e1.weight;  // update the weight
        }
    };

    edge_insertion(e);
    edge_insertion(e.reverse());
}

// remove undirected edge e
void Graph::removeEdge(const Edge &e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto edgeRemoval = [&T = this->table, &n = this->n_edges](const Edge &e1) {
        auto it = std::find_if(begin(T[e1.head]), end(T[e1.head]),
                               [e1](const Edge &ed) { return e1.links_same_nodes(ed); });

        assert(it != end(T[e1.head]));
        T[e1.head].erase(it);  // remove edge e1
        --n;                   // decrement the counter of edges
    };

    edgeRemoval(e);
    edgeRemoval(e.reverse());
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const {
    std::vector<int> dist(size_t(size) + 1);
    std::vector<int> path(size_t(size) + 1);
    std::vector<bool> done(size_t(size) + 1);

    // *** TODO ***

    for (int i = 1; i <= size; ++i) {
        dist[i] = inf;
        path[i] = 0;
        done[i] = false;
    }

    dist[1] = 0;
    done[1] = true;
    int v = 1;
    int totWeight = 0;


    while (true) {

        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
            int u = it->tail; // u is a vertex adjacent to v
            if (done[u] == false && dist[u] > it->weight) { //if dist[u] is inf it hasn't been visited yet
                dist[u] = it->weight;
                path[u] = v;
               
            }
        }

        int distMin = inf;
        // Loop through all vertices
        for (int i = 1; i <= size; i++) {
            // Check if vertice is not visited ad distance is smaller than previous smallest
            if (!done[i] && dist[i] < distMin) {
                // Update smallest distance
                distMin = dist[i];
                v = i;
            }
        }

        if (distMin == inf) break; //exit the loop if we haven't found anything smaller than inf

        // Create new edge and print
        Edge e(path[v], v, dist[v]);
        std::cout << e << std::endl;
        totWeight += dist[v];

                     
        done[v] = true;
    }


    std::cout << "Total weight: " << totWeight << std::endl;

}

// Kruskal's minimum spanning tree algorithm
// T(n,m) = O(mlogm)
void Graph::mstKruskal() const {

    // *** TODO ***
   
    DSets D(size); // n trees with one node each
    int totWeight = 0;
    int counter = 0;
    std::vector<Edge> V;
    

   // Heapify: build the heap with all edges, O(m) inte linjär just nu
    for (int i = 1; i <= size; ++i) {
        auto itr = table[i].begin();
        
        while (itr != table[i].end()) {
           if (i < itr->tail) {
                //H.insert(*itr);
               V.push_back(*itr);
                //V[i] = *itr;
           }
           itr++;
        } 
    }

    Heap<Edge> H{V}; // min-heap by edges cost

    //v är vertex just nu, u är alla edges den kan nå

    // Loop executes m times at most, FÖ14
    while (!H.isEmpty() && counter < size-1) { // Tree must have n-1 edges
        Edge e = H.deleteMin(); // Find an edge with lowest cost: O(logm). e = (v, u)

        // O(1) with smart union and path compression
        if (D.find(e.head) != D.find(e.tail)) { // Do u and v belong to the same tree
         
            D.join(D.find(e.head), D.find(e.tail)); // Merge two different trees
            std::cout << e << std::endl;
            totWeight += e.weight;
            counter++;
        }
                
    }

    std::cout << "Total weight: " << totWeight << std::endl;
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                                            \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        for (auto it = table[v].begin(); it != table[v].end(); ++it) {
            std::cout << " (" << std::setw(2) << it->tail << ", " << std::setw(2) << it->weight
                      << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------------------------------------\n";
}
