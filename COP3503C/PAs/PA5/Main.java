    /*              COP 3503C Assignment 5
    This program is written by: Yurii Hriaziev */

    import java.util.*;

    // class Edge to store each connection between vertices
    class Edge {
        int source, dest, weight;

        public Edge(int source, int dest, int weight) {
            this.source = source;
            this.dest = dest;
            this.weight = weight;
        }
    }

    // class Node to store each vertex in the heap
    class Node {
        int vertex;
        long weight;

        public Node(int vertex, long weight) {
            this.vertex = vertex;
            this.weight = weight;
        }
    }

    // class Graph which will have the list of all edges
    class Graph {
        List<List<Edge>> adjList = null;

        Graph(List<Edge> edges, int n) {
            adjList = new ArrayList<>();

            // create a new list for each list;
            for (int i=0; i<n; i++) {
                adjList.add(new ArrayList<>());
            }

            // add all edges to the list
            for (Edge edge : edges) {
                adjList.get(edge.source).add(edge);
            }
        }
    }

    public class Main {
        static int C;
        static int R;
        static int S;
        static long L;

        // dijkstras: function that will find the shortest distance from capital to all cities
        static long[] dijkstras(Graph graph, int source, int n) {
            PriorityQueue<Node> minHeap = new PriorityQueue<>(Comparator.comparingLong(node -> node.weight));

            minHeap.add(new Node(source, 0));

            long dist[] = new long[n];
            Arrays.fill(dist, Long.MAX_VALUE);

            dist[source] = 0;

            boolean done[] = new boolean[n];

            while (!minHeap.isEmpty()) {
                Node node = minHeap.poll();

                int u = node.vertex;

                for (Edge edge : graph.adjList.get(u)) {
                    int v = edge.dest;
                    int weight = edge.weight;

                    if (done[v] == false && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        minHeap.add(new Node(v, dist[v]));
                    }
                }

                done[u] = true;
            }

            return dist;
        }

        // main function to read input, setup edges, roads, graph, and call shortest path algorithm
        public static void main(String[] args) {
            Scanner input = new Scanner(System.in);

            C = input.nextInt();
            R = input.nextInt();
            S = input.nextInt() - 1;    

            List<Edge> edges = new ArrayList<>();
            List<Edge> roads = new ArrayList<>();

            for (int i=0; i<R; i++) {
                int u = input.nextInt() - 1;
                int v = input.nextInt() - 1;
                int w = input.nextInt();

                roads.add(new Edge(u, v, w));

                edges.add(new Edge(u, v, w));
                edges.add(new Edge(v, u, w));
            }

            L = input.nextLong();

            Graph graph = new Graph(edges, C);

            // call the algorithm here
            long dist[] = dijkstras(graph, S, C);

            // count any treasures that are exactly L distance
            int cityCount = 0;
            for (int i=0; i<C; i++) {
                if (dist[i] == L) {
                    cityCount++;
                }
            }

            // count any that are along the road to the city
            int roadCount = 0;
            for (Edge road : roads) {
                int u = road.source;
                int v = road.dest;
                int w = road.weight;

                long distFromU = L - dist[u];
                long distFromV = L - dist[v];

                boolean foundU = false;
                boolean foundV = false;

                if (distFromU > 0 && distFromU < w) {
                    if (dist[v] + (w - distFromU) >= L) {
                        foundU = true;
                    }
                }

                if (distFromV > 0 && distFromV < w) {
                    if (dist[u] + (w - distFromV) >= L) {
                        foundV = true;
                    }
                }

                if (foundU == true && foundV == true && distFromU + distFromV == w) {
                    roadCount++;
                } else {
                    if (foundU == true) {
                        roadCount++;
                    }
                    if (foundV == true) {
                        roadCount++;
                    }
                }
            }

            System.out.println("In city: " + cityCount);
            System.out.println("On the road: " + roadCount);

            input.close();
        }
    }
