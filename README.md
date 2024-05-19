Mail : yonidil1997@gmail.com
ID : 316529445

In this assignment we were asked to realize a class for representing a graph, and graph graph algorithms class.

------------------The Graph class:---------------------
A Graph is an object that holds an adjacency matrix, and some other variables that hold attributes of the Graph like is it directed?, is it weighted?, and does it have negative weights?
All these attributes will help me later in the algorithms I implemented in the Algorithms class.
In addition we have a function that loads a matrix into a Graph object, and while loading, some tests are performed.
First of all I check that I got a valid matrix (nxn).
And then I put the attributes of the matrix into the match variables.
While loading I also put the number of edges and the number of vertices of the matrix into their variables.


--------------------------Algorithm class:----------------------------
In this class I implemented algorithms on graphs
The algorithms are:

1) static bool isConnected(const Graph& g);
In this algorithm I went through all the vertices and checked if they are connected to each other.
If the graph is directed, then I checked whether it is strongly connected.
I performed a connectivity test using the bfs algorithm, which I also implemented later
There is no need for more than that, even if the graph is with weights, because I checked if there any path, not what is the shortest path.

2) static string shortestPath(const Graph& g, int start, int end);
In this algorithm I checked what is the shortest path between two specific vertices, and according to the properties of the graph I used the appropriate algorithm.
For a graph without weights - BFS algorithm.
For a weighted graph but without negative values ​​- Dijkstra algorithm.
For a graph with negative values ​​- Belman-Ford algorithm.
In case that there is no path or negative cycle- I return -1.


3) static bool isContainsCycle(const Graph& g);
In this function I checked whether a graph contains any circle.
I went through all the vertices, and for each pair of vertices A and B, I checked if there was any path between them, using BFS (not necessarily the shortest).
If there is a path between A and B and also a edge between B and A then there is a circle.
But if the graph is not directed, then if there is an edge between A and B, then it is clear that there is also an edge between B and A, so if the graph is not directed, I took out the edge between A and B and checked if there is a path, and if such a path exists, then - If I return the edge I took out, it will be a circle.

4) static bool isBipartite(const Graph& g);
In this algorithm I chacked whether the graph can be divided into two groups, so that there are no edges between two vertices in the same group
The code goes through all the vertices and if a vertex is not yet colored then I paint it, and put it in a group of the match color. then go over all its neighbors, making sure they are not painted the same color. And if they are not painted in the same color, then I paint them the other color.
And if the vertex has a neighbor that is already painted the same color, then I return false.
After I'm done going through all the vertices I print the groups of colors and return true.

5) static bool negativeCycle(const Graph& g);
In this algorithm I check if there is a negative circle in the graph, and if there is- then I print it.
I do the test using an algorithm that is quite similar to the Bellman-Ford algorithm. But when I get to the nth iteration and I realize that there is indeed a shorter path than what I have found so far, the algorithm knows that there is a negative circle and knows how to print it.

6) BFS algorithm - an algorithm for finding the shortest path between vertices in an unweighted graph

7) Dijkstra algorithm - an algorithm for finding the shortest path between vertices, also in a weighted graph

8) Belman-Ford algorithm - an algorithm for finding the shortest path between vertices, even in a graph with negative weights

COMPLING AND RUN:

    Demo:
        Open the terminal and write  - make demo
        The demo will run outomaticly.

    Test:
        First make sure- line 3 in Test.cpp --uncomment--
        like that:
        //Mail : 
        //ID :
        #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
        #include "doctest.h"
        #include "Algorithms.hpp"
        #include "Graph.hpp"
        .
        */Rest of the code.../*
        .

        Then open the terminal and write  - make test
        The test will run outomaticly.

    tidy:    
        The "make tidy" command is possible but not recommended, because it points to a lot of problems in the docktest.h file and very few "problems" in my code. and all the problems in my code are taken care of and the tidy just can't understand that I took care of them already.

    testCounter:
        First make sure- line 3 in Test.cpp is --in comment--
        like that:
        //Mail : 
        //ID :
        //#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
        #include "doctest.h"
        #include "Algorithms.hpp"
        #include "Graph.hpp"
        .
        */Rest of the code.../*
        .

        Then open the terminal and write  - make testCounter
        The test will run outomaticly.

    valdrind:
        There are two options: (Note that you put the third line of Test.cpp as a comment if you want to run testCounter.cpp and uncomment if you want to run Test.cpp)
            1) Compile the file you want to run, for example test.cpp and then write the command: "valgrind ./test"
                In our case "make test" or "make testCounter".
                Note that in this option, because I defined in the makefile that it will run automatically after compiling, so when you write "make test" it will run automatically and then you can write the command "valgrind ./test" and it will run again but now it will show you all the likked.

                When I ran the code the output was:

                ==12299== 
                ==12299== HEAP SUMMARY:
                ==12299==     in use at exit: 0 bytes in 0 blocks
                ==12299==   total heap usage: 1,175 allocs, 1,175 frees, 203,863 bytes allocated
                ==12299== 
                ==12299== All heap blocks were freed -- no leaks are possible
                ==12299== 
                ==12299== For lists of detected and suppressed errors, rerun with: -s
                ==12299== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

                That is - no leaks.

            2) To compile with Valgrind - "make valgrindTestCounter" or "make valgrindTest".
                note that in this option not all of Valgrind's information appears and if you want to see more information then you have to write the command: "valgrind ./test" or "valgrind ./testCounter after

"make clean" will clean all the .o .exe file
