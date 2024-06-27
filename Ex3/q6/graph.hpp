#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <stack>

class Graph {
private:
    int n; // number of nodes
    std::vector<std::vector<int>> adj; // adjacency matrix

public:
    Graph(int n = 0);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    void printGraph() const;
    void dfs(int v, std::vector<bool>& visited, std::stack<int>& st);
    void dfsTranspose(int v, std::vector<bool>& visited, std::vector<int>& component, const Graph& transposedGraph);
    Graph getTranspose() const;
    std::vector<std::vector<int>> kosaraju();
};

#endif // GRAPH_HPP