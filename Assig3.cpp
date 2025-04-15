#include<iostream>
using namespace std;

const int MAX_NODES = 100; 

class Maze{
private:
    int adj[MAX_NODES][MAX_NODES];  
    int v;  

public:
    Maze(int vertices) {
        v = vertices;
        for(int i = 0; i < MAX_NODES; i++) {
            for(int j = 0; j < MAX_NODES; j++) {
                adj[i][j] = 0;
            }
        }
    }

    void addEdge(int src, int dest) {
        adj[src][dest] = 1;
        adj[dest][src] = 1;  
    }

    void BFS(int start) 
    {
        int visited[MAX_NODES] = {0};
        int queue[MAX_NODES];
        int front = 0, rear = 0;

        visited[start] = 1;
        queue[rear++] = start;

        while(front < rear) {
            int node = queue[front++]; 
            cout << node << " ";

            for(int i = 0; i < v; i++) {
                if(adj[node][i] == 1 && visited[i] == 0) {
                    visited[i] = 1;
                    queue[rear++] = i;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Maze g(5); 

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    cout << "BFS starting from vertex 0:\n";
    g.BFS(0);

    return 0;
}