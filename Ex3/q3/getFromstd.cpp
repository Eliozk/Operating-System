#include <iostream>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

class Graph {
private:
    int n; // number of nodes
    vector<vector<int>> adj; // adjacency matrix

public:
    Graph(int n) {
        this->n = n;
        adj.assign(n + 1, vector<int>(n + 1, 0)); // Initialize adjacency matrix with size (n+1)x(n+1)
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1; // Assuming it's a directed graph
    }

    void dfs(int v, vector<bool>& visited, stack<int>& st) {
        visited[v] = true;
        for (int u = 1; u <= n; ++u) {
            if (adj[v][u] && !visited[u]) {
                dfs(u, visited, st);
            }
        }
        st.push(v);
    }

    void dfsTranspose(int v, vector<bool>& visited, vector<int>& component) {
        visited[v] = true;
        if(visited[v]){
            cout << "added number to korason: " << v << endl;
        }
        component.push_back(v);
        cout << "Visiting node " << v << " in transposed graph" << endl; // Debug print
        for (int u = 1; u <= n; ++u) {
            if (adj[u][v] && !visited[u]) {
                cout << "Going deeper from node " << v << " to node " << u << endl; // Debug print
                dfsTranspose(u, visited, component);
            }
        }
    }

    vector<vector<int>> kosaraju() {
        vector<bool> visited(n + 1, false);
        stack<int> st;

        // Step 1: Perform DFS and fill stack with finishing times
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                dfs(i, visited, st);
            }
        }

        // Step 2: Transpose the graph
        Graph transposedGraph(n);
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (adj[u][v]) {
                    transposedGraph.addEdge(v, u);
                }
            }
        }

        // Clear visited array for reuse in second DFS
        visited.assign(n + 1, false);
        vector<vector<int>> sccs;

        // Step 3: Process nodes in order defined by stack
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            if (!visited[v]) {
                vector<int> component;
                cout << "Processing node " << v << " from stack" << endl; // Debug print
                transposedGraph.dfsTranspose(v, visited, component);
                sccs.push_back(component);
            }
        }

        return sccs;
    }

    void removeEdge(int u, int v) {
        adj[u][v] = 0;
    }

    void printGraph() {
        cout << "Current Graph:" << endl;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph(0); // Initialize graph with 0 nodes

    string line;
    while (getline(cin, line)) {
        cout << "Command received: " << line << endl; // Debug print

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "Newgraph") {
            int n, m;
            ss >> n >> m;
            graph = Graph(n); // Reinitialize graph

            for (int i = 0; i < m; ++i) {
                getline(cin, line);
                stringstream edgeStream(line);
                int u, v;
                edgeStream >> u >> v;
                graph.addEdge(u, v);
            }
        } else if (command == "Kosaraju") {
            vector<vector<int>> sccs = graph.kosaraju();
            
            cout << "Kosaraju command executed.\nThe SCC's are:\n";
            for (const auto& scc : sccs) {
                cout << "SCC: ";
                for (int node : scc) {
                    cout << node << " ";
                }
                cout << endl; // Print each SCC on a new line
            }
        } else if (command == "Newedge") {
            int i, j;
            ss >> i >> j;
            graph.addEdge(i, j);
            cout << "Newedge command: Added edge " << i << " -> " << j << endl; 
        } else if (command == "Removeedge") {
            int i, j;
            ss >> i >> j;
            graph.removeEdge(i, j);
            cout << "Removeedge command: Removed edge " << i << " -> " << j << endl; 
        } else {
            // Handle invalid command or end of input
            break;
        }
        
        // Debug print current state of the graph
        graph.printGraph(); // Make sure you have a printGraph() method to visualize the graph state
        cout << endl; // Add extra line for clarity
    }

    return 0;
}

/**
 * To run all:
 *   run:   "make"
 *   Then run: "./main < input.txt"
 */
