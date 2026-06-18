package COP3503C.week06;

import java.util.*;

public class SkipList {
    final public static int NEG_INF = Integer.MIN_VALUE;
    final public static int POS_INF = Integer.MAX_VALUE;
    
    public static Random rndObj = new Random();
    
    private ArrayList<node> levels;
    private int size;
    
    public SkipList() {
        levels = new ArrayList<>();
        levels.add(buildLevel(0));
        size = 1;
    }

    public node buildLevel(int id) {
        node first = new node(NEG_INF, id);
        node last = new node(POS_INF, id);

        // connect them
        first.next = last;
        last.prev = first;

        // always return the first of the level
        return first;
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

    public boolean insert(int value) {
        // find the value and build the before list
        ArrayList<node> BL = search(value);

        // check if given value is already in the list
        if (BL.get(0).next.data == value) {
            return false;
        }

        // create a null current node
        node curNode = null;

        // start the coin flip while loop
        int i = 0;
        while (i<=size) {
            // create the coin variable (0 or 1)
            int coin;
            if (i==0) {
                coin = 1; // force the coin to be 1 on first iteration of loop (must add the item)
            } else {
                coin = rndObj.nextInt(2); // other iterations of i we choose randomly 0 or 1
            }

            // break out of the loop if coin is 0
            if (coin == 0) {
                break;
            }

            // create the new node if coin is 1 with value and i as the level
            node newNode = new node(value, i);

            // update the up, down
            if (i>0) {
                // add copy of new node to up
                curNode.up = newNode;
                // point to the current node for the new node's down
                newNode.down = curNode;
            }

            // we reached the top of list, and coin is 1 -> create a new level and connect it
            if (i == size) {
                // create the new level
                node newLevel = buildLevel(size);
                // add the new level to levels array
                levels.add(newLevel);
                // connect the new level to the last level in levels
                connectLastLevel();
                // add the new level to before list
                BL.add(newLevel);
            }

            // connect the new node to the neighboring nodes
            node pNode = BL.get(i);
            node nNode = pNode.next;

            // add the new node, first connect neighbors to new node and then new node to neighbors
            newNode.prev = pNode;
            newNode.next = nNode;
            pNode.next = newNode;
            nNode.prev = newNode;

            // Need to update the object's size and get out.
            if (i == size) {
                size++;
                break;
            }

            // go to next level and update curNode
            i++;
            curNode = newNode;
        }

        // return true on successful insertion
        return true;
    }

    public ArrayList<node> search(int value) {
        // first build the before list
        ArrayList<node> BL = new ArrayList<>();

        // get the walker node which is the top left most node of the list
        node walker = levels.get(size-1);

        // loop for the size descending 
        for (int i=size-1; i>=0; i--) {
            while (walker.next.data < value) {
                walker = walker.next;
            }
            // add horizontal node to before list
            BL.add(walker);

            // check if we can go down now
            if (walker.down != null) {
                walker = walker.down;
            }
        }

        // reverse the list
        Collections.reverse(BL);
        return BL;
    }

    public boolean delete(int value) {
        // find the value and get the before list
        ArrayList<node> BL = search(value);
        // get the bottom most node
        node bottom = BL.get(0); // 0 because the list was reversed

        // check if the next value of that bottom is not the value we are looking to delete
        if (bottom.next.data != value) {
            return false;
        }

        // access our delete target
        node curNode = bottom.next;

        // we need to delete all instances of that node
        // run a while loop until cur is null
        while (curNode != null) {
            // do the patching
            // store prev and next node respective of the curNode
            node pNode = curNode.prev;
            node nNode = curNode.next;

            // patch the hole
            pNode.next = nNode;
            nNode.prev = pNode;

            // go up the level
            curNode = curNode.up;
        }

        // check if we have the top level empty -> shrink
        if (size>1 && topLevelSize() == 2) {
            levels.remove(size-1);
            size--;
        }

        // return true on successful deletion of value
        return true;
    }

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

    public static void main(String[] args) {
        SkipList mySkipList = new SkipList();

        // Do 10 inserts.
        for (int i = 0; i < 10; i++) {
            // Generate the item.
            int item = rndObj.nextInt(1000);
            System.out.println("Inserting: " + item);
            
            // Insert it.
            boolean flag = mySkipList.insert(item);
            
            // Print what happened.
            if (flag) {
                System.out.println("Inserted " + item);
            } else {
                System.out.println("Rejected " + item);
            }
            
            // See all the lists.
            mySkipList.printAllLevels();
        }
    }
}

class node {
    public int data;
    public node next, prev, up, down;
    public int level;

    public node(int val, int lvl) {
        data = val;
        level = lvl;
        next = null;
        prev = null;
        up = null;
        down = null;
    }
}