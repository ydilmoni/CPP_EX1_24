#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector> 



namespace ariel {
    class Graph {
    private:
        vector<vector<int>> matrix_graph;
        int num_of_vertices;
        int num_of_edges;
        bool isDirected;
        bool isWeighted;
        bool haveNegative;

    public:
        Graph(){}; // Constructor
        ~Graph(){}; // Destructor

        
        void loadGraph(const vector<vector<int>>& matrix);
        void printGraph() const;
        int getNumOfvertices() const { 
            return num_of_vertices; 
        }
        int getNumOfEdges() const {
             return num_of_edges; 
        }
        const vector<vector<int>>& getMatrixGraph() const { 
            return matrix_graph; 
        }
        bool getIsDirected() const { 
            return isDirected; 
        } 
        bool getIsWeighted() const { 
            return isWeighted; 
        } 
        bool getHaveNegative() const { 
            return haveNegative; 
        } 

    

        static bool validateSquareMatrix(const vector<vector<int>>& matrix);
    };
}

#endif // GRAPH_HPP
