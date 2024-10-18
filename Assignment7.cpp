#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

    struct Edge {
        int src, dest, weight;
    };

    vector<Edge> edges;

    int find(int parent[], int i) {
        if (parent[i] == i)
            return i;
        return find(parent, parent[i]);
    }

    void Union(int parent[], int rank[], int x, int y) {
        int xroot = find(parent, x);
        int yroot = find(parent, y);
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    static bool compare(Edge a, Edge b) {
        return a.weight < b.weight;
    }

public:
    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
        edges.push_back({u, v, w});
    }

    void kruskalMST() {
        vector<Edge> result;
        int parent[V], rank[V];

        for (int i = 0; i < V; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        sort(edges.begin(), edges.end(), compare);

        for (auto &edge : edges) {
            int x = find(parent, edge.src);
            int y = find(parent, edge.dest);

            if (x != y) {
                result.push_back(edge);
                Union(parent, rank, x, y);
            }
        }

        cout << "Edges in Kruskal's MST:\n";
        for (auto &edge : result) {
            cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        }
    }

    void primMST() {
        int key[V], parent[V];
        bool mstSet[V];

        for (int i = 0; i < V; i++) {
            key[i] = INT_MAX;
            mstSet[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < V - 1; count++) {
            int min = INT_MAX, u;
            for (int v = 0; v < V; v++) {
                if (!mstSet[v] && key[v] < min) {
                    min = key[v];
                    u = v;
                }
            }

            mstSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] && !mstSet[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }

        cout << "Edges in Prim's MST:\n";
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " : " << adjMatrix[i][parent[i]] << endl;
        }
    }

    void displayAdjMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int V, choice, u, v, w;
    cout << "Enter the number of departments (nodes): ";
    cin >> V;

    Graph graph(V);

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Find MST using Kruskal's Algorithm\n";
        cout << "4. Find MST using Prim's Algorithm\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter source, destination and weight: ";
                cin >> u >> v >> w;
                graph.addEdge(u, v, w);
                break;
            case 2:
                graph.displayAdjMatrix();
                break;
            case 3:
                graph.kruskalMST();
                break;
            case 4:
                graph.primMST();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
