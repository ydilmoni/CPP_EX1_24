#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector> 



namespace ariel {
    class Graph {
    private:
        std::vector<std::vector<int>> matrix_graph;
        int num_of_vertices;
        int num_of_edges;
        bool isDirected;
        bool isWeighted;
        bool haveNegative;

    public:
        Graph(); // Constructor
        ~Graph(); // Destructor

        // Member functions
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        int getNumOfvertices() const { 
            return num_of_vertices; 
        }
        int getNumOfEdges() const {
             return num_of_edges; 
        }
        const std::vector<std::vector<int>>& getMatrixGraph() const { 
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

    

        static bool validateSquareMatrix(const std::vector<std::vector<int>>& matrix); // Static member function
    };
}

#endif // GRAPH_HPP
