//Mail : yonidil1997@gmail.com
//ID : 316529445

/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"

using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
    ariel::Graph g;
    

    // 5x5 matrix that represents a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
        
        };

    g.loadGraph(graph2); 
    
    g.printGraph();                                    
    cout << Algorithms::isConnected(g) << endl;       
    cout << Algorithms::shortestPath(g, 2, 0) << endl; 
    cout << Algorithms::negativeCycle(g) << endl;   
    cout << Algorithms::isBipartite(g) << endl;        
}