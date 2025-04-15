#include <iostream>
using namespace std;

#define MAX 10
#define INF 9999

void addEdge(int adj[MAX][MAX], int u, int v, int cost) {
    adj[u][v] = cost;
}

void dijkstra(int adj[MAX][MAX], int n, int src, string names[MAX]) {
    int dist[MAX];
    int visited[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min_dist = INF;
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && adj[u][v] != INF && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    int total_cost = 0;
    cout << "Shortest paths from " << names[src] << ":\n";
    cout << "Location\tDistance (Cost)\n";

    for (int i = 0; i < n; i++) {
        cout << names[i] << "\t\t";
        if (dist[i] == INF)
            cout << "Not Reachable\n";
        else {
            cout << dist[i] << "\n";
            total_cost += dist[i]; 
        }
    }

    cout << "\nTotal cost of transportation from " << names[src] << ": " << total_cost << endl;
}

int main() {
    int adj[MAX][MAX];
    int n = 5;

    string names[MAX] = {
        "Supplier",
        "Warehouse",
        "Distribution",
        "RetailStore1",
        "RetailStore2"
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = INF;

    for (int i = 0; i < n; i++)
        adj[i][i] = 0;

    addEdge(adj, 0, 1, 4);
    addEdge(adj, 1, 2, 2);
    addEdge(adj, 2, 3, 5);
    addEdge(adj, 2, 4, 7);
    addEdge(adj, 0, 2, 10);
    addEdge(adj, 1, 4, 8);

    int src = 0; 
    dijkstra(adj, n, src, names);

    return 0;
}
