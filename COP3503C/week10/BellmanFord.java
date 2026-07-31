package COP3503C.week10;

import java.util.*;


public class BellmanFord {
    class Edge {
        int src, dest, weight;
    
        Edge() {
            src = dest = weight = 0;
        }
    }
    
    int V, E;
    Edge edge[];

    BellmanFord(int v, int e) {
        V = v;
        E = e;
        edge = new Edge[e];
        for (int i=0; i<e; i++) {
            edge[i] = new Edge();
        }
    }

    void bellmanFordAlgo(BellmanFord graph, int src) {
        int V = graph.V;
        int E = graph.E;
        int dist[] = new int[V];

        for (int i=0; i<E; i++) {
            dist[i] = Integer.MAX_VALUE;
        }

        dist[src] = 0;

        for (int i=0; i<V; i++) {
            for (int j=0; j<E; j++) {
                int u = graph.edge[j].src;
                int v = graph.edge[j].dest;
                int weight = graph.edge[j].weight;
                if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        for (int j=0; j<E; j++) {
            int u = graph.edge[j].src;
            int v = graph.edge[j].dest;
            int weight = graph.edge[i].weight;

            if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                System.out.println("Negative cycle detected");
                return;
            }
        }
    }

    void printArr(int dist[], int V) {
        System.out.println("Vertex Distance from Source");

        for (int i=0; i<V; i++) {
            
        }
    }
}
