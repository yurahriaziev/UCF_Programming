package COP3503C.week07;

import COP3503C.week04.DetectCycle;

public class DisjointSet {
    private pair[] parents;

    public static void main(String[] args) {
        int[][] edges = {{0, 1}, {0, 3}, {2, 3}};
        int num_vertices = 4;
        
        DisjointSet mySet = new DisjointSet(num_vertices);


    }

    public DisjointSet(int n) {
        parents = new pair[n];

        for (int i=0; i<n; i++) {
            parents[i] = new pair(i, 0);
        }
    }

    int find(int id) {
        if (parents[id].getID() == id) {
            return id;
        }

        int res = find(parents[id].getID());

        if (res != parents[id].getID()) {
            parents[id].setID(res);
            parents[res].decHeight();
        }

        return res;
    }

    boolean union(int id1, int id2) {
        int r1 = find(id1);
        int r2 = find(id2);

        if (r1 == r2) {
            return false;
        }

        int h1 = parents[r1].getHeight();
        int h2 = parents[r2].getHeight();

        if (h1 < h2) {
            parents[r1].setID(r2);
        } else if (h2 < h1) {
            parents[r2].setID(r1);
        } else {
            parents[r2].setID(r1);
            parents[r1].incHeight();
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
