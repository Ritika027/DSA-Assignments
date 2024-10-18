#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
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

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        vector<bool> sptSet(V, false);
        dist[src] = 0;

        for (int count = 0; count < V - 1; count++) {
            int min = INT_MAX, u;

            for (int v = 0; v < V; v++) {
                if (!sptSet[v] && dist[v] <= min) {
                    min = dist[v];
                    u = v;
                }
            }

            sptSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (!sptSet[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }

        cout << "Shortest distances from source " << src << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "To node " << i << " = " << dist[i] << endl;
        }
    }
};

int main() {
    int V, choice, u, v, w, src;
    cout << "Enter the number of landmarks (nodes): ";
    cin >> V;

    Graph graph(V);

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Find Shortest Path using Dijkstra's Algorithm\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter source, destination, and distance: ";
                cin >> u >> v >> w;
                graph.addEdge(u, v, w);
                break;
            case 2:
                graph.displayAdjMatrix();
                break;
            case 3:
                cout << "Enter source node for Dijkstra's algorithm: ";
                cin >> src;
                graph.dijkstra(src);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
