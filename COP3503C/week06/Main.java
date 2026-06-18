package COP3503C.week06;

// Skip List Implementation Skeleton. 

import java.util.*;

public class Main {

    final public static int NEG_INF = Integer.MIN_VALUE;
    final public static int POS_INF = Integer.MAX_VALUE;
    
    public static Random rndObj = new Random();
    
    private ArrayList<node> levels;
    private int size;
    
    // Makes an empty list.
    public Main() {
        // Initially, I am just one level with min and max.
        levels = new ArrayList<node>();
        levels.add(buildLevel(0));
        size = 1;
    }

    // This builds level id to be an empty level.
    public node buildLevel(int id) {
        node first = new node(NEG_INF, id);
        node last = new node(POS_INF, id);
        first.next = last;
        last.prev = first;		
        return first;
    }
    
    // Returns a list of nodes at each level that are right before value.
    public ArrayList<node> search(int value) {
        ArrayList<node> BL = new ArrayList<>();

        node walker = levels.get(size-1);

        for (int i=size-1; i>=0; i--) {
            while (walker.next.data < value) {
                walker = walker.next;
            }
            BL.add(walker);
            if (walker.down != null) {
                walker = walker.down;
            }
        }

        Collections.reverse(BL);
        return BL;
    }
    
    //****************************
    // Inserts value into the set, returns true iff the value was inserted. (False means the
    // value was already in the set.
    public boolean insert(int value) {
        ArrayList<node> BL = search(value);

        // check if the value we are trying to add already exists in the list, if so return false
        if (BL.get(0).next.data == value) {
            return false;
        }

        node cur = null;
        int i=0; // start of the coin flip loop

        while (i <= size) {
            int coin;
            if (i==0) {
                coin = 1;
            } else {
                coin = rndObj.nextInt(2);
            }
            if (coin == 0) break; // break if coin is 0

            node newNode = new node(value, i);
            // update up, down, left, right

            if (i>0) {
                cur.up = newNode;
                newNode.down = cur;
            }

            // reach top of list
            if (i == size) {
                node nextLevel = buildLevel(size);
                levels.add(nextLevel);
                connectLastLevel();
                BL.add(nextLevel);
            }

            // connecting nodes
            node tmpLow = BL.get(i);
            node tmpNext = tmpLow.next;
            newNode.prev = tmpLow;
            newNode.next = tmpNext;
            tmpLow.next = newNode;
            tmpNext.prev = newNode;

            if (i == size) {
                size++;
                break;
            }

            cur = newNode;
            i++;
        }
        return true;
    }
    
    // Deletes value from the list. Returns true if value was in the list and was deleted.
    // Returns false if value wasn't in the list and takes no action.
    public boolean delete(int value) {
        ArrayList<node> BL = search(value);
        node bottom = BL.get(0);

        // check if searched item is present
        if (bottom.next.data != value) {
            return false;
        }

        node cur = bottom.next;

        while (cur != null) {
            node pNode = cur.prev;
            node nNode = cur.next;
            pNode.next = nNode;
            nNode.prev = pNode;

            cur = cur.up;
        }

        if (size>1 && topLevelSize() == 2) {
            levels.remove(size-1);
            size--;
        }

        return true;
    }
    
    // Returns the number of items on the top level.
    private int topLevelSize() {
        node cur = levels.get(size - 1);
        int sz = 0;
        while (cur != null) {
            cur = cur.next;
            sz++;
        }
        return sz;
    }
    
    // Connects the last level to the rest of the lists.
    public void connectLastLevel() {
        node top = levels.get(size-1);
        node below = levels.get(size-2);

        top.down = below;
        below.up = top;

        // end of top list
        top = top.next;
        // go to end of second to top list
        while (below.next.data != POS_INF) {
            below = below.next;
        }
        // list right sides up and down
        top.down = below;
        below.up = top;
    }
    
    // For debugging.
    public void printAllLevels() {
        System.out.println(levels.size() + " and " + size);
        for (int i = 0; i < size; i++) {
            System.out.print("Level " + i + ": ");
            printLevel(i);
        }
        System.out.println("---------------------------");
    }
    
    // Prints level id. For debugging.
    public void printLevel(int id) {
        node walker = levels.get(id);
        while (walker != null) {
            System.out.print(walker.data + " ");
            walker = walker.next;
        }
        System.out.println();
    }
    
    // Basic insert test.
    public static void basicInsertTest() {
        // Create the object.
        Main mine = new Main(); //this constructor creates a level as well
        
        // Do 10 inserts.
        for (int i = 0; i < 10; i++) {
            // Generate the item.
            int item = rndObj.nextInt(1000);
            System.out.println("Gen " + item);
            
            // Insert it.
            boolean flag = mine.insert(item);
            
            // Print what happened.
            if (flag) {
                System.out.println("Inserted " + item);
            } else {
                System.out.println("Rejected " + item);
            }
            
            // See all the lists.
            mine.printAllLevels();
        }
        
        //Let us delete
        Scanner sc = new Scanner(System.in);
        int item = 0;
        while (item != -1) {
            System.out.println("Enter an item to delete: ");
            item = sc.nextInt();
            boolean flag = mine.delete(item);
            if (flag) {
                System.out.println("Deleted " + item);
                mine.printAllLevels();
            } else {
                System.out.println(item + " can not be deleted.");
            }
        }
    }
    
    public static void main(String[] args) {
        // largeTestRandom();
        basicInsertTest();
    }
}

class node {
    public int data;
    public node next, prev, up, down;
    public int level;
  
    public node(int myval, int mylev) {
        data = myval;
        level = mylev;
        next = null;
        prev = null;
        up = null;
        down = null;
    }
}
