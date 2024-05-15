#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

// Test for the isConnected function
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
}

// Test for the shortestPath function
TEST_CASE("Test shortestPath") {
    ariel::Graph g;

    // Simple connected graph
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    // Disconnected graph, no path exists
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    // Graph with direct path
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");

    // Graph with no edges
    vector<vector<int>> graph4 = {
        {0, 0},
        {0, 0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "-1");
}

// Test for the isContainsCycle function
TEST_CASE("Test isContainsCycle") {
    ariel::Graph g;

    // No cycle
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    // Contains cycle
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    // Single node, no cycle
    vector<vector<int>> graph3 = {
        {0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    // Two nodes, no cycle
    vector<vector<int>> graph4 = {
        {0, 0},
        {0, 0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);
}

// Test for the isBipartite function
TEST_CASE("Test isBipartite") {
    ariel::Graph g;

    // Bipartite graph
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isBipartite(g) == true);

    // Non-bipartite graph
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == false);

    // Graph with multiple edges and bipartite
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == true);

    // Single node, bipartite
    vector<vector<int>> graph4 = {
        {0}
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == true);
}

// Test for invalid graph loading
TEST_CASE("Test invalid graph") {
    ariel::Graph g;

    // Invalid graph with different number of edges in rows
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}
    };
    CHECK_THROWS(g.loadGraph(graph1));

    // Valid but sparse graph
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}
    };
    CHECK_NOTHROW(g.loadGraph(graph2));
}
