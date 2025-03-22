#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// Structure to represent a weighted edge in the graph
struct Edge {
    int destination;
    int weight;
    Edge(int dest, int w) : destination(dest), weight(w) {}
};

class Graph {
private:
    int V; // Number of vertices
    vector<vector<Edge>> adjacencyList;

public:
    // Constructor
    Graph(int vertices) : V(vertices) {
        adjacencyList.resize(vertices);
    }

    // Function to add an edge to the graph
    void addEdge(int source, int destination, int weight) {
        adjacencyList[source].push_back(Edge(destination, weight));
        adjacencyList[destination].push_back(Edge(source, weight)); // For undirected graph
    }

    // Dijkstra's algorithm implementation
    vector<int> dijkstra(int startVertex) {
        // Priority queue to store vertices and their distances
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Vector to store distances from start vertex
        vector<int> distances(V, numeric_limits<int>::max());
        
        // Distance to start vertex is 0
        distances[startVertex] = 0;
        pq.push({0, startVertex});

        while (!pq.empty()) {
            int currentVertex = pq.top().second;
            int currentDistance = pq.top().first;
            pq.pop();

            // If current distance is greater than stored distance, skip
            if (currentDistance > distances[currentVertex]) {
                continue;
            }

            // Check all adjacent vertices
            for (const Edge& edge : adjacencyList[currentVertex]) {
                int newDistance = distances[currentVertex] + edge.weight;

                // If new distance is shorter, update distance
                if (newDistance < distances[edge.destination]) {
                    distances[edge.destination] = newDistance;
                    pq.push({newDistance, edge.destination});
                }
            }
        }

        return distances;
    }
};

// Example usage
int main() {
    // Create a graph with 6 vertices
    Graph g(6);

    // Add edges
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);

    // Find shortest paths from vertex 0
    int startVertex = 0;
    vector<int> distances = g.dijkstra(startVertex);

    // Print the shortest distances
    cout << "Shortest distances from vertex " << startVertex << ":\n";
    for (int i = 0; i < distances.size(); i++) {
        cout << "To vertex " << i << ": " << distances[i] << endl;
    }

    return 0;
}