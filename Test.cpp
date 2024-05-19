//Mail : yonidil1997@gmail.com
//ID : 316529445
// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected") {
    ariel::Graph g;

    // Simple connected graph
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    // Disconnected graph
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    // Single node graph
    vector<vector<int>> graph3 = {
        {0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    // Two node disconnected graph
    vector<vector<int>> graph4 = {
        {0, 0},
        {0, 0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    // Graph with multiple components
    vector<vector<int>> graph5 = {
        {0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == false);

}

TEST_CASE("Test shortestPath") {
    ariel::Graph g;

    // Simple graph with path
    vector<vector<int>> graph1 = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    // Weighted graph without negative weights
    vector<vector<int>> graph2 = {
        {0, 2, 0, 0},
        {2, 0, 3, 1},
        {0, 3, 0, 1},
        {0, 1, 1, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) =="0->1->3");

    // Graph with negative weights without path
    vector<vector<int>> graph3 = {
        {0, -2, 0, 0},
        {-2, 0, -3, 1},
        {0, -3, 0, 1},
        {0, 1, 1, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "-1");

    // Graph with negative weights with negative cycle
     vector<vector<int>> graph4 = {
        {0, -2, 2, 0},
        {-2, 0, -3, 1},
        {2, -3, 0, 0},
        {0, 1, 0, 0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "-1");


    // Graph with negative weights with path
     vector<vector<int>> graph5 = {
        {0, 1, -2, 0},
        {1, 0, -4, 1},
        {0, 0, 0, -3},
        {0, 0, 0, 0}
    };
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    // simple graph without path
    vector<vector<int>> graph6 = {
        {0, 0, 1},
        {0, 0, 0},
        {1, 0, 0}
    };
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "-1");

    // Fully connected graph
    vector<vector<int>> graph7 = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->3");


}

TEST_CASE("Test isContainsCycle with simple graph") {
    ariel::Graph g;

    // Simple graph with a cycle
    vector<vector<int>> graph1 = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    // Simple graph without a cycle
    vector<vector<int>> graph2 = {
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

     // Simple graph with multiple cycles
    vector<vector<int>> graph3 = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

}

TEST_CASE("Test isContainsCycle with directed graph, no-negative") {
    ariel::Graph g;

    // directed graph with a cycle
    vector<vector<int>> graph1 = {
        {0, 2, 0, 0},
        {0, 0, 4, 0},
        {0, 0, 0, 3},
        {0, 1, 0, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    // directed graph without a cycle
    vector<vector<int>> graph2 = {
        {0, 0, 0, 0, 0},
        {0, 0, 5, 0, 0},
        {2, 0, 0, 9, 0},
        {6, 0, 0, 0, 0},
        {4, 5, 0, 2, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

     // directed graph with multiple cycles
    vector<vector<int>> graph3 = {
        {0, 3, 0, 0, 0},
        {0, 0, 5, 0, 0},
        {2, 0, 0, 9, 0},
        {6, 0, 0, 0, 2},
        {4, 5, 0, 2, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

}

TEST_CASE("Test isContainsCycle with directed graph && negative value") {
    ariel::Graph g;

    // directed graph with a cycle but not negative cycle
    vector<vector<int>> graph1 = {
        {0, 3, 0, 0},
        {0, 0, 5, 0},
        {-2, 0, 0, 4},
        {-5, 0, 0, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    // directed graph without a cycle
    vector<vector<int>> graph2 = {
        {0, 0, 0, 0, 0},
        {0, 0, -6, 8, 0},
        {-8, 0, 0, -4, 0},
        {6, 0, 0, 0, 5},
        {4, 0, 0, 0, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

     // directed graph with multiple cycles 
    vector<vector<int>> graph3 = {
        {0, 3, 0, -6, 0},
        {0, 0, 4, -2, 0},
        {5, 0, 0, -10, 0},
        {0, 0, 0, 0, -5},
        {3, 2, 0, 0, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

}

TEST_CASE("Test isBipartite") {
    ariel::Graph g;

    // Single node graph
    vector<vector<int>> graph1 = {
        {0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isBipartite(g) == true);

    // Graph with an odd cycle (triangle)
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == false);

    // Graph with an even cycle (square)
    vector<vector<int>> graph3 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == true);

    // fuli connected graph
    vector<vector<int>> graph4 = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == false);

    // helf connected graph
    vector<vector<int>> graph5 = {
        {0, 1, 4, 1},
        {0, 0, 5, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isBipartite(g) == false);

    vector<vector<int>> graph6 = {
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isBipartite(g) == true);

}

TEST_CASE("Test negativeCycle") {
    ariel::Graph g;

    // Graph with zero weights
    vector<vector<int>> graph1 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::negativeCycle(g) == false);

    // Graph with multiple negative edges but no cycle
    vector<vector<int>> graph2 = {
        {0, -1, 0, 0},
        {-1, 0, -1, 0},
        {0, -1, 0, -1},
        {0, 0, -1, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == false);

    // Graph with cycle but not negative one
    vector<vector<int>> graph3 = {
        {0, -1, 0},
        {0, 0, 2},
        {4, 0, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == false);

    // Graph without negative value
    vector<vector<int>> graph4 = {
        {0, 2, 0},
        {2, 0, 3},
        {0, 3, 0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == false);

    // Graph with cycle but not negative one
    vector<vector<int>> graph5 = {
        {0, -1, 0},
        {0, 0, -5},
        {4, 0, 0}
    };
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::negativeCycle(g) == true);

    //graph with one cycle
    vector<vector<int>> graph6 = {
        {0, 2, 0, 0, -3},
        {0, 0, 3, -5, 0},
        {0, 0, 0, 20, 0},
        {-6, 0, 0, 0, -30},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::negativeCycle(g) == true);

    //graph with a multiple negative cycle
    vector<vector<int>> graph7 = {
        {0, 2, 0, 0, 0},
        {0, 0, 3, -5, 0},
        {0, 0, 0, 20, 0},
        {-6, 0, 0, 0, -30},
        {1, 0, 0, 0, 0}
    };
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::negativeCycle(g) == true);

    //graph with a cycle with sum 0
    vector<vector<int>> graph8 = {
        {0, 2, 0, 0, 0},
        {0, 0, 3, -5, 0},
        {0, 0, 0, 0, 0},
        {3, 0, 0, 0, -30},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::negativeCycle(g) == false);

    
}

TEST_CASE("Test load graph") {
    ariel::Graph g;

    // Graph with self edge
    vector<vector<int>> graph1 = {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    CHECK_THROWS(g.loadGraph(graph1));

    // Graph with negative self edge 
    vector<vector<int>> graph2 = {
        {0, -1, 4},
        {-1, -5, 2},
        {4, 2, 0}
    };
    CHECK_THROWS(g.loadGraph(graph2));

    // Single node with a self-loop
    vector<vector<int>> graph3 = {
        {1}
    };
    CHECK_THROWS(g.loadGraph(graph3));

    // Empty graph
    vector<vector<int>> graph4 = {};
    CHECK_THROWS(g.loadGraph(graph4));

}
