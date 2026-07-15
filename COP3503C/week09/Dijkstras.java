package COP3503C.week09;

import java.util.*;

// make edge class
class Edge {
    int source, dest, weight;

    public Edge(int source, int dest, int weight) {
        this.source = source;
        this.dest = dest;
        this.weight = weight;
    }
}

// class to store heap node
class Node {
    int vertex, weight;

    public Node(int vertex, int weight) {
        this.vertex = vertex;
        this.weight = weight;
    }
}

// graph class which will have list of edges
class Graph {
    List<List<Edge>> adjList = null;

    Graph(List<Edge> edges, int n) {
        adjList = new ArrayList<>();

        // create a new list for each list
        for (int i=0; i<n; i++) {
            adjList.add(new ArrayList<>());
        }

        // add edges to the directed graph
        for (Edge edge: edges) {
            adjList.get(edge.source).add(edge);
        }
    }
}

public class Dijkstras {
    private static void getRoute(int[] prev, int i, List<Integer> route) {
        if (i >= 0) {
            getRoute(prev, prev[i], route);
            route.add(i);
        }
    }

    public static void findShortestPath(Graph graph, int source, int n) {
        // create min heap p-queue using the weight as the index -> Comparator.comparingInt(node -> node.weight)
        PriorityQueue<Node> minHeap = new PriorityQueue<>(Comparator.comparingInt(node -> node.weight));
        
        // add the source to the heap and save its weight/dist as 0
        minHeap.add(new Node(source, 0));

        // set initial distance from source to all other vertexes to infinity
        List<Integer> dist = new ArrayList<>(Collections.nCopies(n, Integer.MAX_VALUE));

        // distance from the source to itself is 0
        dist.set(source, 0);

        // boolean list track verticies to which min distance is already found
        boolean[] done = new boolean[n];
        // mark the source as found
        done[source] = true;

        // stores predecessor of a vertex (to a print path)
        int[] prev = new int[n];
        // set prev of source to -1 since there is nothing before the source
        prev[source] = -1;

        // run until min heap is empty
        while (!minHeap.isEmpty()) {
            // remove and return the min vertex
            Node node = minHeap.poll();

            // get the vertex number
            int u = node.vertex;

            // go to each connection of the given vertex
            for (Edge edge: graph.adjList.get(u)) {
                int v = edge.dest;
                int weight = edge.weight;

                // check if we are not done with that vertex
                if (!done[v] && (dist.get(u) + weight ) < dist.get(v)) {
                    dist.set(v, dist.get(u)+weight);
                    prev[v] = u;
                    minHeap.add(new Node(v, dist.get(v)));
                }
            }

            // mark the poped node as done
            done[u] = true;
        }

        // print the result
        List<Integer> route = new ArrayList<>();
        for (int i=0; i<n; i++) {
            if (i != source && dist.get(i) != Integer.MAX_VALUE) {
                getRoute(prev, i, route);
                System.out.printf("Path (%d -> %d): Minumum Cost = %d, Route = %s\n", source, i, dist.get(i), route);
                route.clear();
            }
        }
    }

    public static void main(String[] args) {
        // list of all edges and their weights
        List<Edge> edges = Arrays.asList(
            new Edge(0, 1, 10), new Edge(0, 4, 3), new Edge(1, 2, 2),
            new Edge(1, 4, 4), new Edge(2, 3, 9), new Edge(3, 2, 7),
            new Edge(4, 1, 1), new Edge(4, 2, 8), new Edge(4, 3, 2)
        );

        // total number of nodes
        int n = 5;

        Graph graph = new Graph(edges, n);

        // run dijkstras algorithm from every node
        for (int src=0; src<n; src++) {
            findShortestPath(graph, src, n);
        }
    }
}
