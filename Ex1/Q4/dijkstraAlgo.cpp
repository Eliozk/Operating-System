// C++ program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph
#include <iostream>
#include <limits.h>
#include <vector>
#include <assert.h>
using namespace std;



// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(const vector<int> &dist, const vector<bool> &sptSet, int V)
{
    int min = INT_MAX;
    int min_index = -1; // Initialize min_index to a default value
    for (int v = 0; v < V; v++)
    {
        if (!sptSet[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}
void printGraph(const vector<vector<int>> &graph)
{
    for (const auto &row : graph)
    {
        for (int weight : row)
        {
            cout << weight << " ";
        }
        cout << endl;
    }
}

// A utility function to print the constructed distance
// array
void printSolution(const vector<int> &dist, int V)
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << "  " << i << " \t\t\t" << dist[i] << endl;
    }
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(const vector<vector<int>> &graph, int src, int V)
{
    vector<int> dist(V, INT_MAX);  // The output array. dist[i] will hold the shortest distance from src to i
    vector<bool> sptSet(V, false); // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    cout << "The Matrix of the graph: " << endl;
    printGraph(graph);
    // Print the constructed distance array
    printSolution(dist, V);
}

void InputMatrix(int row, int col, vector<vector<int>> &graph)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int weight;
            if (!(cin >> weight) || weight < 0)
            {
                cout << "Invalid input for matrix element. Number should be a non-negative integer." << endl;
                exit(1); // Exit the program in case of invalid input
            }
            graph[i][j] = weight;
        }
    }
}


// Driver's code
int main()
{

    int row = -1, col = -1;
    // Check for exactly two positive integers
    cout << "Enter the number of rows and columns of the adjacency matrix: ";
    if (scanf("%d%d", &row, &col) != 2 || row <= 0 || col <= 0)
    {
        cout << "Invalid input: Number of rows and columns must be positive integers." << endl;
        return -1;
    }

    vector<vector<int>> graph(row, vector<int>(col));
    cout << "Enter the adjacency matrix:" << endl;
    InputMatrix(row, col, graph); // Get the adjacency matrix from the user
    int lastVertex = graph.size();
    int src;
    // Get the source vertex from the user
    cout << "Enter the source vertex between 0 Vertex and " << lastVertex -1 << " : ";
    if (scanf("%d", &src) != 1)
    {
        cout << "Invalid input: Source vertex must be an integer between 0 and " << lastVertex << "." << endl;
        return 1;
    }
    if (src < 0 || src >= lastVertex)
{
    cout << "Invalid input: Source vertex must be between 0 and " << lastVertex << "." << endl;
    return 1;
}
   
    // Function call
    dijkstra(graph, src, row);

    return 0;
}
