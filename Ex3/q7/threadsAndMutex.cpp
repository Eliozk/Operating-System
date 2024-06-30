#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <mutex>
#include <poll.h>

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
        cout << "New edge added between " << u << " and " << v << endl;
    }

    void removeEdge(int u, int v) {
        adj[u][v] = 0;
        cout << "Removed the edge between " << u << " and " << v << endl;
    }

    void printGraph() const {
        cout << "Current Graph:" << endl;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
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

    void dfsTranspose(int v, vector<bool>& visited, vector<int>& component, const Graph& transposedGraph) {
        visited[v] = true;
        component.push_back(v);
        for (int u = 1; u <= n; ++u) {
            if (transposedGraph.adj[v][u] && !visited[u]) {
                dfsTranspose(u, visited, component, transposedGraph);
            }
        }
    }

    Graph getTranspose() const {
        Graph transposedGraph(n);
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (adj[u][v]) {
                    transposedGraph.addEdge(v, u);
                }
            }
        }
        return transposedGraph;
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
        Graph transposedGraph = getTranspose();

        // Clear visited array for reuse in second DFS
        visited.assign(n + 1, false);
        vector<vector<int>> sccs;

        // Step 3: Process nodes in order defined by stack
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            if (!visited[v]) {
                vector<int> component;
                transposedGraph.dfsTranspose(v, visited, component, transposedGraph);
                sccs.push_back(component);
            }
        }

        return sccs;
    }
};

std::mutex graphMutex;
std::mutex threadCountMutex;
//main is one thread and every added client we will add one. n+1 threads for n clients.
int threadCount = 1;

void handleClientCommands(int clientSocket, Graph& graph) {
    {
        std::lock_guard<std::mutex> lock(threadCountMutex);
        ++threadCount;
        cout << "Thread created for client.\nTotal thread count: " << threadCount << "\nClients amount connected to server: " << threadCount - 1 << endl;
    }

    char buffer[1024] = {0};
    while (true) {
        int valread = read(clientSocket, buffer, 1024);
        if (valread <= 0) {
            if (valread == 0) {
                cout << "Client disconnected." << endl;
            } else {
                perror("recv");
            }
            close(clientSocket);
            {
                std::lock_guard<std::mutex> lock(threadCountMutex);
                --threadCount;
                cout << "Thread closed for client. Total current thread count: " << threadCount << endl;
            }
            return;
        }

        stringstream ss(buffer);
        string command;
        ss >> command;

        if (command == "Newgraph") {
            int n, m;
            ss >> n >> m;

            // Lock graph for Mutex
            std::lock_guard<std::mutex> lock(graphMutex);

            graph = Graph(n); // Reinitialize graph

            for (int i = 0; i < m; ++i) {
                memset(buffer, 0, sizeof(buffer));
                valread = read(clientSocket, buffer, 1024);
                if (valread == 0) {
                    cout << "Client disconnected while sending graph edges." << endl;
                    close(clientSocket);
                    {
                        std::lock_guard<std::mutex> lock(threadCountMutex);
                        --threadCount;
                        cout << "Thread closed for client. Current thread count: " << threadCount << endl;
                    }
                    return;
                }
                stringstream edgeStream(buffer);
                int u, v;
                edgeStream >> u >> v;
                graph.addEdge(u, v);
            }
        } else if (command == "Kosaraju") {
            // Lock graph for reading
            std::lock_guard<std::mutex> lock(graphMutex);

            vector<vector<int>> sccs = graph.kosaraju();

            stringstream response;
            response << "Kosaraju command executed.\nThe SCC's are:\n";
            for (const auto& scc : sccs) {
                for (int node : scc) {
                    response << node << " ";
                }
                response << endl; // Print each SCC on a new line
            }
            send(clientSocket, response.str().c_str(), response.str().length(), 0);
        } else if (command == "Newedge") {
            int i, j;
            ss >> i >> j;
            cout << "Newedge command: adding edge " << i << " -> " << j << endl;

            // Lock graph for modification
            std::lock_guard<std::mutex> lock(graphMutex);

            graph.addEdge(i, j);
            send(clientSocket, "Newedge command executed successfully.\n", strlen("Newedge command executed successfully.\n"), 0);
        } else if (command == "Removeedge") {
            int i, j;
            ss >> i >> j;
            cout << "Removeedge command: Removing edge " << i << " -> " << j << endl;

            // Lock graph for modification
            std::lock_guard<std::mutex> lock(graphMutex);

            graph.removeEdge(i, j);
            send(clientSocket, "Removeedge command executed successfully.\n", strlen("Removeedge command executed successfully.\n"), 0);
        } else {
            // Handle invalid command or end of input
            send(clientSocket, "Invalid command.\n", strlen("Invalid command.\n"), 0);
        }

        // Debug print current state of the graph
        {
            std::lock_guard<std::mutex> lock(graphMutex);
            graph.printGraph(); // Make sure you have a printGraph() method to visualize the graph state
        }
        cout << endl; // Add extra line for clarity
    }
}

void clientHandler(int clientSocket, Graph& graph) {
    handleClientCommands(clientSocket, graph);
}

int main() {
    int serverSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    Graph graph(0); // Initialize graph with 0 nodes

    // Creating socket file descriptor
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 9034
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9034);

    // Forcefully attaching socket to the port 9034
    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serverSocket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cout << "Server opened and now listening for clients to connect" << endl;

    while (true) {
        int clientSocket;
        //this line gets clients connections
        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Create a new thread to handle client commands
        std::thread(clientHandler, clientSocket, std::ref(graph)).detach();
    }

    close(serverSocket);
    return 0;
}
