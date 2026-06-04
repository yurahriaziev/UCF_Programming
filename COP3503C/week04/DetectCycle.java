package COP3503C.week04;

public class DetectCycle {
    private pair[] parents;
    public static void main(String[] args) {
        int[][] edges = {{0, 1}, {0, 3}, {2, 3}};
        int num_vertices = 4;
        
        DetectCycle mySet = new DetectCycle(num_vertices);

        System.out.println("Detecting a cycle...");
        if (mySet.hasCycle(edges)) {
            System.out.println("Cycle detected");
        } else {
            System.out.println("Cycle not detected");
        }
    }
    public DetectCycle(int n) {
        parents = new pair[n];

        for (int i=0; i<n; i++) {
            parents[i] = new pair(i, 0);
        }
    }

    boolean hasCycle(int[][] edges) {
        for (int i=0; i<edges.length; i++) {
            int a = edges[i][0];
            int b = edges[i][1];

            if (union(a, b) == false) {
                return true;
            }
        }

        return false;
    }

    int find(int id) {
        while (parents[id].getID() != id) {
            id = parents[id].getID();
        }

        return id;
    }

    boolean union(int id1, int id2) {
        int root1 = find(id1);
        int root2 = find(id2);

        if (root1 == root2) {
            return false;
        }

        int h1 = parents[root1].getHeight();
        int h2 = parents[root2].getHeight();

        if (h1 < h2) {
            parents[root1].setID(root2);
        } else if (h2 < h1) {
            parents[root2].setID(root1);
        } else {
            parents[root2].setID(root1);
            parents[root1].incHeight();
        }

        return true;
    }
}

class pair {
    private int id; // parent
    private int height;

    public pair(int id, int height) {
        this.id = id;
        this.height = height;
    }

    public int getID() {
        return id;
    }

    public void setID(int id) {
        this.id = id;
    }

    public int getHeight() {
        return height;
    }

    public void incHeight() {
        height++;
    }
    
    public void decHeight() {
        height--;
    }
}
