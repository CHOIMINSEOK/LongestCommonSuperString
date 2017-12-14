//
//  Graph.hpp
//  ShortestCommonSuperstring
//
//  Created by Minseok Choi on 14/12/2017.
//  Copyright © 2017 Minseok Choi. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <list>
#include <limits.h>

using namespace std;

class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    bool isCyclicUtil(int v, bool visited[], bool *rs);  // used by isCyclic()
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph when it doesn't make a cycle
    void removeEdge(int v, int w);
    
    bool isCyclic();    // returns true if there is a cycle in this graph
    int getFirstSetIdx();
};
#endif /* Graph_hpp */
