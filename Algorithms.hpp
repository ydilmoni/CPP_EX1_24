#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>
using namespace std;

namespace ariel {
    class Algorithms {
        public:
            static bool isConnected(const Graph& g);
            static string shortestPath(const Graph& g, int start, int end);
            static string isContainsCycle(const Graph& g);
            static string isBipartite(const Graph& g);
            static string negativeCycle(const Graph& g);
            static vector<int> bfs(const vector<vector<int>>& matrix, int start, int end);
            static vector<int> dijkstra (const vector<vector<int>>& matrix, int start, int end);
            static vector<int> belmanFordAlgorithm(const vector<vector<int>>& matrix, int start);
            static string printPath(vector<int>&parents, int start, int end);
            static string printNegativePath(vector<int> &parents,const vector<vector<int>>& matrix, int start);
    };
}

#endif // ALGORITHMS_HPP
