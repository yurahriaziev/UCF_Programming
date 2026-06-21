// package COP3503C.PAs.PA3;

import java.util.Scanner;

/*              COP 3503C Assignment ##
This program is written by: Yurii Hriaziev */

public class Main {
    static int n;
    static int m;
    static int d;
    
    static Edge edges[];
    static int delList[];
    static boolean existsList[];
    static long resList[];

    // main function to read test input, create the disjoint set,
    //  generate the true/false connections list and perform union
    //  only on the existing connections first, then work backwards
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        n = input.nextInt();
        m = input.nextInt();
        d = input.nextInt();

        edges = new Edge[m+1];
        delList = new int[d];
        existsList = new boolean[m+1];
        resList = new long[d + 1];

        for (int i=1; i<=m; i++) {
            existsList[i] = true;
        }

        for (int i=1; i<=m; i++) {
            int u = input.nextInt();
            int v = input.nextInt();

            edges[i] = new Edge(u, v);
        }

        for (int i=0; i<d; i++) {
            delList[i] = input.nextInt();
            existsList[delList[i]] = false;
        }

        DisjointSet mySet = new DisjointSet(n);

        for (int i=1; i<=m; i++) {
            if (existsList[i] == true) {
                mySet.union(edges[i].u, edges[i].v);
            }
        }

        resList[d] = mySet.getConnectivity();

        for (int i=d-1; i>=0; i--) {
            int edgeToAdd = delList[i];

            mySet.union(edges[edgeToAdd].u, edges[edgeToAdd].v);

            resList[i] = mySet.getConnectivity();
        }

        for (int i=0; i<=d; i++) {
            System.out.println(resList[i]);
        }

        input.close();
    }
}

// Edge class to store each connection edge
class Edge {
    int u;
    int v;

    public Edge(int a, int b) {
        this.u = a;
        this.v = b;
    }
}

// Disjointset class which has find, union by rank, and get connectivity methods
class DisjointSet {
    private Pair parents[];
    private long size[];
    private long connectivity;

    public DisjointSet(int n) {
        parents = new Pair[n+1];
        size = new long[n+1];
        connectivity = n;

        for (int i=1; i<=n; i++) {
            parents[i] = new Pair(i, 0);
            size[i] = 1;
        }
    }

    // find: function that will find the root of a given using path compression
    public int find(int id) {
        if (id == parents[id].getID()) {
            return id;
        }

        int res = find(parents[id].getID());

        if (res != parents[id].getID()) {
            parents[id].setID(res);
            // parents[res].decHeight();
        }

        return res;
    }

    // union: function that will perform union operation on two sets if they dont have same root
    // does union by rank and updates connectivity
    public boolean union(int id1, int id2) {
        int root1 = find(id1);
        int root2 = find(id2);

        if (root1 == root2) {
            return false;
        }

        connectivity -= size[root1] * size[root1];
        connectivity -= size[root2] * size[root2];

        int height1 = parents[root1].getHeight();
        int height2 = parents[root2].getHeight();

        if (height1 < height2) {
            parents[root1].setID(root2);
            size[root2] += size[root1];
            connectivity += size[root2] * size[root2];
        } else if (height2 < height1) {
            parents[root2].setID(root1);
            size[root1] += size[root2];
            connectivity += size[root1] * size[root1];
        } else {
            parents[root2].setID(root1);
            parents[root1].incHeight();

            size[root1] += size[root2];
            connectivity += size[root1] * size[root1];
        }

        return true;
    }

    public long getConnectivity() {
        return connectivity;
    }
}

// Pair class to store set pairs of id and height
class Pair {
    private int id;
    private int height;

    public Pair(int id, int height) {
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

    public void decHeight() {
        height--;
    }

    public void incHeight() {
        height++;
    }
}