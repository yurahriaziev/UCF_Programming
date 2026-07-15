package COP3503C.week09;

import java.util.*;

public class Graph {
    private int V; // # of vertex
    private LinkedList<Integer> adj[]; // Adjacency List
    
    // constructor
    @SuppressWarnings("unchecked")
    Graph(int v) {
        V = v;
        adj = new LinkedList[v];
        for (int i=0; i<v; ++i) {
            adj[i] = new LinkedList<Integer>();
        }
    }

    // function to add an edge into the graph
    void addEdge(int v, int w) {
        adj[v].add(w);
        adj[w].add(v);
    }

    // int s -> starting point
    void BFS(int s) {
        // boolean visited array
        boolean visited[] = new boolean[V];

        // queue of integers as LinkedList
        LinkedList<Integer> queue = new LinkedList<>();

        // mark the starting point as visited
        visited[s] = true;
        // enqueue the starting point
        queue.add(s);

        // start looping while the queue is not empty
        while (queue.size() != 0) {
            // dequeue
            int explore = queue.poll();
            // print that deqeueued element
            System.out.println(explore + " ");

            // create an iterator for the linkedlist of the explore item from adjacency list
            Iterator<Integer> i = adj[explore].listIterator();
            // loop while there is next item in linked list
            while (i.hasNext()) {
                // get the next item
                int n = i.next();
                if (!visited[n]) {
                    visited[n] = true;
                    queue.add(n);
                }
            }
        }
    }

    void BFS2(int s) {
        boolean[] visited = new boolean[V];
        LinkedList<Integer> queue = new LinkedList<>();

        visited[s] = true;
        queue.add(s);

        while (!queue.isEmpty()) {
            int explore = queue.poll();
            System.out.println(explore + " ");

            Iterator<Integer> i = adj[explore].listIterator();
            while (i.hasNext()) {
                int n = i.next();
                if (!visited[n]) {
                    visited[n] = true;
                    queue.add(n);
                }
            }
        }
    }

    // void 

    void DFSUtil(int v, boolean visited[]) {
        // mark start point visited
        visited[v] = true;

        // print v out;
        System.out.println(v + " ");

        // create integer iterator to loop through the adjacency list
        Iterator<Integer> i = adj[v].listIterator();

        // loop while there is a next item in the linked list
        while (i.hasNext()) {
            // get next vertex
            int n = i.next();

            // push i and start exploring from n if n is unvisited
            if (!visited[n]) {
                DFSUtil(n, visited);
            }
        }
    }

    void DFS2Util(int v, boolean[] visited) {
        visited[v] = true;
        System.out.println(v + " ");

        Iterator<Integer> i = adj[v].listIterator();
        while (i.hasNext()) {
            int n = i.next();

            while (!visited[n]) {
                DFS2Util(n, visited);
            }
        }
    }

    void DFS() {
        boolean visited[] = new boolean[V];

        // perform dfs on all nodes that are not visited, good for separated graphs
        for (int i=0; i<V; i++) {
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    void DFS2() {
        boolean[] visited = new boolean[V];

        for (int i=0; i<V; i++) {
            if (!visited[i]) {
                DFS2Util(i, visited);
            }
        }
    }
}
