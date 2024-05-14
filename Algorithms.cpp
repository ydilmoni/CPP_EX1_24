#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <limits>
#include <stack>
#include <iostream>
#include <climits>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;

namespace ariel
{


    bool Algorithms::isConnected(const Graph &g)//סיימתי
    {
        vector< vector<int>> matrix = g.getMatrixGraph();
        int vertex = matrix.size();
        vector<int> resultFromSerchAlgo(vertex);
        
        //אם הגרף לא מכוון אפשר פשוט לבדוק אם ניתן להגיע מקודקוד 0 לכל שאר הגרף, אחרת צריך לבדוק עבור כל קודקוד
        int iteration = g.getIsDirected()? vertex : 1;
        for (int i=0; i<iteration; i++){
            for (int j=0; j<vertex; j++){
                if(i!=j){
                    //השימוש באלגוריתם הזה לכל סוג של גרף, ללא קשר למשקלים שליליים או חיוביים הוא בגלל שאני רק מחפש דרך כלשהיא ולא מעניין אותי המרחק
                    resultFromSerchAlgo=bfs(matrix,i,j);
                    if(printPath(resultFromSerchAlgo,i,j) == "There is no path from vertex "+ to_string(i) +" to vertex " +to_string(j)){
                        cout<<"The graph is not connected!!"<<endl;
                        cout<<"For example:\
                        \nThere is no path from vertex "+ to_string(i) +" to vertex " +to_string(j)<<endl;
                        return false;
                    }
                }                
            }
        }

        cout<<"The graph is connected!! YAY!";
        return true;
    }

    string Algorithms::shortestPath(const Graph &g, int start, int end) // סיימתי
    {
        if (start < 0 || end < 0 || start > g.getNumOfvertices() - 1 || end > g.getNumOfvertices() - 1)
        {
            // כלומר אם ביקשת את הפעולה עבור קודקודים שלא נמצאים בכלל
            return "Out of range!\n you must ask for values between 0 and " +to_string(g.getNumOfvertices() - 1);
        }

        if (start == end)
        {
            return "Start and end vertices are the same.";
        }

        vector<vector<int>> matrix = g.getMatrixGraph();
        vector<int> parents;

        if (!g.getIsWeighted())
        {
            if (matrix[start][end])//אם זה גרף ללא משקלים, ויש צלע בין הקודקודים שביקשת אז זה בהכרח הכי קצר
            {
                return "(" + to_string(start) + ") -> (" + to_string(start) + ")";
            }
            parents= bfs(matrix, start, end);
            return printPath(parents, start, end);
        }

        if (!g.getHaveNegative())//אם גרף ממושקל ללא משקלים שליליים נשתמש בדייקסטרה
        {
            cout << "using Dijkstra's algorithm to find the shortest path from: \nvertex "
                 << start << " to vertex "
                 << end << endl;
            parents = dijkstra(matrix, start, end);
            return printPath(parents, start, end);
        }

        cout << "There is a negative value in the graph.\
        \nUsing Bellman-Ford algorithm to find the shortest path from\
         \nvertex " +to_string(start) + " to vertex " +to_string(end)<<endl;

        parents  = belmanFordAlgorithm(matrix, start);
        return printPath(parents, start, end);
    }

    string Algorithms::isContainsCycle(const Graph &g)//סיימתי
    {
        int vertex = g.getNumOfvertices();
        vector<vector<int>> matrix = g.getMatrixGraph();
        vector<bool> visited (vertex, false);
        string result;
        vector<int> parentsIJ(vertex,-1);
        vector<int> parentsJI(vertex, -1);


        for (int i=0; i<vertex; i++){
            for (int j=0; j<vertex; j++){
                if(i!=j){
                    parentsIJ = bfs(matrix,i,j);
                    parentsJI = bfs(matrix,j,i);
                    if (parentsIJ[j]!=-1 && parentsJI[i]!=-1){
                        result = "There is a cycle in the graph: \n";
                        int k=j;
                        while (parentsIJ[k] != -1){
                            result += "( "+to_string(k) +" ) <- ";
                            k=parentsIJ[k];
                        }
                        k=i;
                        while ((parentsJI[k] != -1))
                        {
                            result += "( "+to_string(k) +" ) <- ";
                            k=parentsJI[k];
                        }
                        result += "( "+to_string(k) +" )";
                        return result;
                    }

                }                
            }
        }

         return "No cycle found.";
    }

    string Algorithms::isBipartite(const Graph &g)//סיימתי
    {
        vector<vector<int>> matrix = g.getMatrixGraph();
        int numVertices = g.getNumOfvertices();

        vector<int> colors(numVertices, -1); // מעקב אחרי צבעים
        vector<vector<int>> groups(2);//קבוצות החלוקה       
        queue<int> q;                        

        for (int i = 0; i < numVertices; i++)//מעבר על כל הקודקודים
        {
            if (colors[i] == -1)//אם אתה עדיין לא צבוע
            {
                colors[i] = 0;//נצבע אותך בצבע 0          
                groups[0].push_back(i); //ונוסיף אותך לקבוצה 0
                q.push(i);

                while (!q.empty())
                {
                    int current = q.front();
                    q.pop();

                    
                    for (int neighbor = 0; neighbor < matrix[current].size(); neighbor++)//מעבר על כל השכנים
                    {
                        if (matrix[current][neighbor])//אם קיימת צלע ביניהם
                        {
                           
                            if (colors[neighbor] == -1) //אם השכן לא צבוע 
                            {
                                colors[neighbor] = 1 - colors[current];//נצבע אותו בצבע ההפוך מהקודקוד הנוכחי
                                groups[colors[neighbor]].push_back(neighbor);//נוסיף את השכן לקבוצה שלו
                                q.push(neighbor);
                            }
                            //אם לשכן יש אותו צבע כמו לנוכחי אז הם לא ניתנים לחלוקה ל2
                            else if (colors[neighbor] == colors[current])
                            {
                                return "The graph is not bipartite.";
                            }
                        }
                    }
                }
            }
        }

        //הדפסה של הקבוצות
        string result = "Bipartite groups:\nGroup A: ";
        for (int vertex : groups[0])
        {
            result += to_string(vertex) + " ";
        }
        result += "\nGroup B: ";
        for (int vertex : groups[1])
        {
            result += to_string(vertex) + " ";
        }

        return result;
    }

    string Algorithms::negativeCycle(const Graph &g)
    {
        if (!g.getHaveNegative() || !g.getIsWeighted())
        {
            return "There is no negative values in this graph --> There is no negative cycle ";
        }

        
        vector<vector<int>> matrix = g.getMatrixGraph();
        int n = g.getNumOfvertices();
        vector<int> distances(n,INT_MAX);
        vector<int> parents(n,-1);
        distances[0]=0;
        
        string result;

        for (size_t i = 0; i < n-1; i++)
        {
            for(size_t u = 0; u < n ; u++ ){
                for(size_t v = 0; v < n; v++) {
                    if(matrix[u][v]!=0 && distances[v] > distances[u] + matrix[u][v]){
                        distances[v] = distances[u] + matrix[u][v];
                        parents[v] = u;
                    }
                }
            }
        }
        
        for(size_t u = 0; u < n ; u++ ){
                for(size_t v = 0; v < n; u++) {
                    if(matrix[u][v]!=0 && distances[v] > distances[u] + matrix[u][v]){
                        return printNegativePath(parents, matrix, 0);
                    }
                }
            }

        
        
        
        // parents=belmanFordAlgorithm(matrix,0);
        // if (parents[parents.size()-1] == -3){
        //     for(int i = parents.size()-2; i>=0; i-- ){
        //         result += " ( "+ to_string(parents[i]) + " ) -->";
        //     }
        //     return result;
        // }
        // for (size_t i=0;i<n; i++){
        //     int u,v;
        //     parents=belmanFordAlgorithm(matrix, i);
        //     for (size_t j = 0; j < parents.size(); j++)
        //     {
        //        if (parents[j]<-1)
        //        {
        //         v=j;
        //         if (parents[j]==-5)
        //         {
        //             u=0;
        //         }else{
        //             u=(parents[v]+5)/-3;//מצאתי את הקודקודים שגרמו למעגל
        //         }
        //         parents[v]=u;
        //         int corrent = u;
        //         cout<<"V is "<<v<<endl;
        //         while (parents[corrent]!=v)
        //         {
        //             result = result+ " ( "+ to_string(corrent) +" ) -> ";
        //             corrent=parents[corrent];
        //         }
        //         result =result + " ( "+ to_string(u) +" )";
                
        //         return result;
        //        }
        //     }
            
            
        // }
        
        return "There is no a negative cycle";
    }

    vector<int> Algorithms::bfs(const vector<vector<int>> &matrix, int start, int end)//סיימתי
    {
        queue<int> Q; // ככה קראו לתור באלגו 1. זרמתי
        int vertex = matrix.size();
        vector<string> colors(vertex, "white");
        vector<int> distans(vertex, INT_MAX);
        vector<int> parents(vertex, -1); // יסמן אין הורים כרגע, אולי יהיו הורים אחר כך
        colors[start] = "gray";
        distans[start] = 0;
        parents[start] = -1;
        Q.push(start);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for (int v = 0; v < vertex; v++)
            {
                if (matrix[u][v] != 0 && v != u)
                {
                    if (colors[v] == "white")
                    {
                        colors[v] = "gray";
                        distans[v] = distans[u] + 1;
                        parents[v] = u;
                        Q.push(v);
                    }
                }
            }
            colors[u] = "black";
        }
        return parents;
    }

    vector<int> Algorithms::dijkstra(const vector<vector<int>> &matrix, int start, int end)//סיימתח
    {

        vector<int> distances(matrix.size(), INT_MAX);
        vector<int> parents(matrix.size(), -1);

        auto compare = [&distances](int a, int b) {
            return distances[a] > distances[b];
        };

        priority_queue<int, vector<int>, decltype(compare)> pq(compare);

        distances[start] = 0;
        pq.push(start); 

        while (!pq.empty())
        {
            int u = pq.top();
            pq.pop();
            for (int v = 0; v < matrix.size(); v++)
            {
                if (matrix[u][v] != 0 && distances[v] > distances[u] + matrix[u][v])
                {
                    distances[v] = distances[u] + matrix[u][v];
                    parents[v] = u;
                    pq.push(v); 
                }
            }
        }


        return parents;
    }

    vector<int> Algorithms::belmanFordAlgorithm(const vector<vector<int>>& matrix, int start)//סיימתי
    {
        

        int n = matrix.size();

        vector<int> distances(n, INT_MAX);
        vector<int> parents(n,-1);
        distances[start] = 0;
        for (int i = 0; i < n-1; i++)
        {
            for (int u = 0; u < n; u++)
            {
                for (int v = 0; v < n; v++)//עבור כל צלע
                {
                    if (u!=v && matrix[u][v]!=0 && distances[u]!=INT_MAX && distances[v] > distances[u] + matrix[u][v] ){
                        distances[v] = distances[u] + matrix[u][v];
                        parents[v] = u;
                        
                    }
                }
            }
        }
        
        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                if (matrix[u][v]!=0 &&distances[u]!=INT_MAX&& (distances[v] > distances[u] + matrix[u][v]) )
                {   
                    cout<<"u "<<u<<" and distance is "<< distances[u]<<" and dad is "<< parents[u]<<endl;
                    cout<<"v "<<v<<" and distance is "<< distances[v]<<" and dad is "<< parents[v]<<endl;
                    // cout<<"u "<<u<<" and distance is "<< distances[u]<<endl;
                    // cout<<"u "<<u<<" and distance is "<< distances[u]<<endl;
                    
                    vector <int> cycle;
                    int current = v;

                    // while (parents[current]!=-1 && parents[current] !=start)
                    // {
                    //     cout<<"current is "<<current<<" and parent is "<< parents[current]<<endl;
                    //     cycle.push_back(current);
                    //     current = parents[current];
                    // }
                    // if ( parents[current]==start)
                    // {
                    //     cycle.push_back(current);
                    //     cycle.push_back(start);
                    //     cycle.push_back(-3);//כדי לזהות שמדובר במערך הורים של מעגל שלילי
                    // }
                    
                    return cycle;
                }
            }
        }
        return parents;
    }

    string Algorithms::printPath(vector<int> &parents, int start, int end)//סיימתי
    {
        
        if (parents[parents.size()-1]==-3){
            return "Error: there is a negative cycle.";//קיבלתי את הסימון של בלמן פורד לכך שיש מעגל שלילי
        }
        
        if(parents[end] == start){
            return "( " + to_string(start) + " ) -> ( " + to_string(end) + " ) ";
        }
        
        string result;
        int current = end;
        while (parents[current] != start)
        {
            result = "-> ( " + to_string(current) + " ) " + result;
            current = parents[current];
        }

        if (result == ""){
            return "There is no path from vertex "+ to_string(start) +" to vertex " +to_string(end);
        }
        result = "( " + to_string(current) + " ) " + result;
        
        return result;
    }

    string Algorithms::printNegativePath(vector<int> &parents,const vector<vector<int>>& matrix, int start)
    {
        string result;
        int n = parents.size();
        vector<bool> visited(n,false);
        int u = start;

        while (!visited[u])
        {
            visited[u] = true;
            u = parents[u];
        }

        int v = parents[u];
        cout << "Negative cycle found: "<<endl;
        result += "{{ "+ to_string(u)+" }} ";
        
        while (v != u) {
        
        // result += "--( W: "+to_string(matrix[v][parents[v]])+ " ) -->> {{ "+ to_string(v)+" }} "; // אם רוצים לראות גם משקלים
        result += "---->> {{ "+ to_string(v)+" }} ";
        v = parents[v];
        }
        // result += "--( W: "+to_string(matrix[v][parents[v]])+ " )-->> {{ "+ to_string(u)+" }} ";//אם רוצים עם משלקים
        result += "---->> {{ "+ to_string(u)+" }} ";
                        
        return result;
    }
}
