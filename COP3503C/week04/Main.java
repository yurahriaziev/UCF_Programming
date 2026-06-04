package COP3503C.week04;

import java.util.*;

public class Main {

    // A little driver program to test our class.
    public static void main(String[] args) {

        Scanner stdin = new Scanner(System.in);

        System.out.println("How many items do you want in your Disjoint Set?");
        int n = stdin.nextInt();

        Main mySet = new Main(n); //make the sets

        // Keep on going till the user wants to quit.
        while (true) {

            System.out.println("Do you want to quit(1=yes, 0=no)?");
            int ans = stdin.nextInt();
            if (ans == 1) break;

            // Get the two items to union.
            System.out.println("Which two items do you want to bring together, 0 through "+(n-1)+"?");
            int item1 = stdin.nextInt();
            int item2 = stdin.nextInt();

            // See if it worked!
            boolean result = mySet.union(item1, item2);

            if (!result) {
                System.out.println("Sorry, those were already together!");
            }
            else {
                System.out.println("The union was successful, here is the new parent list: "+mySet);
            }
        }
    }

    private pair[] parents;

    // Create the initial state of a disjoint set of n elements, 0 to n-1.
    // Makeset
    public Main(int n) {

        parents = new pair[n];

        for (int i=0; i<n; i++) {
            parents[i] = new pair(i, 0);
        }
    }

    // Returns the root node of the tree storing id.
    public int find(int id) {
        while (parents[id].getID() != id) {
            id = parents[id].getID();
        }

        return id;
    }

    public boolean union(int id1, int id2) {
        int root1 = find(id1);
        int root2 = find(id2);

        if (root1 == root2) {
            return false;
        }

        int height1 = parents[root1].getHeight();
        int height2 = parents[root2].getHeight();

        if (height1 < height2) {
            parents[root1].setID(root2);
        } else if (height1 > height2) {
            parents[root2].setID(root1);
        } else {
            parents[root2].setID(root1);
            parents[root1].incHeight();
        }

        return true;
    }

    // Just represents this object as a list of each node's parent.
    public String toString() {
        String ans = "";
        for (int i=0; i<parents.length; i++) {
            if(i == parents[i].getID()) {
                ans = ans + "(" + i + ", " + parents[i].getID() + ":" + parents[i].getHeight() + ") ";
            } else {
                ans = ans + "(" + i + ", " + parents[i].getID() + ") ";
            }
        }
        return ans;
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
}