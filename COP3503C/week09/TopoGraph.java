package COP3503C.week09;

import java.util.*;

public class TopoGraph {
    // # of vertices
    private int V;

    // adjacency list as ArraList of ArrayLists
    private ArrayList<ArrayList<Integer> > adj;

    TopoGraph(int v) {
        V = v;

        adj = new ArrayList<ArrayList<Integer>>(v);
        for (int i=0; i<v; i++) {
            adj.add(new ArrayList<Integer>());
        }
    }

    // add edge to directed graph
    void addEdge(int v, int w) {
        adj.get(v).add(w);
    }

    int topoDFS(int v, boolean visited[], int tracker, int ordering[]) {
        // mark v as visited
        visited[v] = true;

        // create iterator of that v adjacent list and loop while there are elements
        Iterator<Integer> iter = adj.get(v).iterator();
        while (iter.hasNext()) {
            int n = iter.next();

            // if element is not visited recurse deaper into that adjacency list
            if (!visited[n]) {
                tracker = topoDFS(n, visited, tracker, ordering);
            }
        }

        // update ordering
        ordering[tracker] = v;

        // return updated tracker
        return tracker - 1;
    }

    // function to perform topological sort, uses recursive topologicalSortUtil()
    void topologicalSort() {
        // visited array
        boolean visited[] = new boolean[V];

        // list of ints to keep topology order
        int[] topoOrder = new int[V];
        int tracker = V-1;

        for (int i=0; i<V; i++) {
            if (!visited[i]) {
                tracker = topoDFS(i, visited, tracker, topoOrder);
            }
        }

        for (int i=0; i<V; i++) {
            System.out.print(topoOrder[i] + " ");
        }
    }

    public static void main(String[] args) {
        TopoGraph g = new TopoGraph(6);
        g.addEdge(5, 2);
        g.addEdge(5, 0);
        g.addEdge(4, 0);
        g.addEdge(4, 1);
        g.addEdge(2, 3);
        g.addEdge(3, 1);

        System.out.println("Topo Sort:");
        g.topologicalSort();
    }
}
