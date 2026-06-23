package COP3503C.week07;

import java.util.*;

public class SkipList {
    final public static int NEG_INF = Integer.MIN_VALUE;
    final public static int POS_INF = Integer.MAX_VALUE;
    
    public static Random rndObj = new Random();
    
    private ArrayList<node> levels;
    private int size;

    // Returns the number of items on the top level.
    private int topLevelSize() {
        node cur = levels.get(size-1);
        int topSize = 0;
        while (cur.next != null) {
            topSize++;
            cur = cur.next;
        }

        return topSize;
    }

    public node buildLevel(int id) {
        node first = new node(NEG_INF, id);
        node last = new node(POS_INF, id);

        first.next = last;
        last.prev = first;

        return first;
    }

    public void connectLastLevel() {
        // get the top and second to top first nodes
        node top = levels.get(size-1);
        node below = levels.get(size-2);

        // connect the first node of top and bottom both ways
        top.down = below;
        below.up = top;

        // go to the last node in the top level (only NEG_INF --> POS_INF)
        top = top.next;
        while (below.next.data != POS_INF) {
            below = below.next;
        }

        top.down = below;
        below.up = top;
    }

    public ArrayList<node> search(int value) {
        // create the before list
        ArrayList<node> BL = new ArrayList<>();

        // access the walker at the top of the levels
        node walker = levels.get(size-1);

        // loop for the size of levels
        for (int i=size-1; i>=0; i--) {
            while (walker.next.data < value) {
                walker = walker.next;
            }

            BL.add(walker);

            if (walker.down != null) {
                walker = walker.down;
            }
        }

        // reverse before list and return it
        Collections.reverse(BL);
        return BL;
    }

    public boolean delete(int value) {
        // search and build the before list
        ArrayList<node> BL = search(value);

        // get access to the bottom most node of before list
        node bottom = BL.get(0);
        // check if the next value does not equal to the value to to delete
        if (bottom.next.data != value) {
            return false;
        }

        // get access to the node to delete
        node curNode = bottom.next;

        // run a while loop until curNode is null
        while (curNode != null) {
            node pNode = curNode.prev;
            node nNode = curNode.next;

            pNode.next = nNode;
            nNode.prev = pNode;

            curNode = curNode.up;
        }

        // remove the top level size if needed
        if (size>=1 && topLevelSize() == 2) {
            levels.remove(size-1);
            size--;
        }

        // return true on successful deletion
        return true;
    }

    public boolean insert(int value) {
        // search and build before list
        ArrayList<node> BL = search(value);

        // check if value to add already is in list
        if (BL.get(0).next.data == value) {
            return false;
        }

        // create the current node walker
        node curNode = null;

        // start a while loop that will run while its less than or equal to size
        int i = 0;
        while (i <= size) {
            // flip the coin
            int coin;
            if (i == 0) {
                coin = 1;
            } else {
                coin = rndObj.nextInt(2);
            }

            // check if coin is 0 -> don't add and break
            if (coin == 0) {
                break;
            }

            // create new node to add
            node newNode = new node(value, i);
            // check if we are on level other than 0
            if (i > 0) {
                curNode.up = newNode;
                newNode.down = curNode;
            }

            // check if we hit the size of levels then build new level, add to BL and connect
            if (i == size) {
                node newLevel = buildLevel(size);
                levels.add(newLevel);
                connectLastLevel();
                BL.add(newLevel);
            }

            // add new node and connect neighbors
            node pNode = BL.get(i);
            node nNode = pNode.next;

            // connect neighbors to new node first
            newNode.prev = pNode;
            newNode.next = nNode;

            // connect new node to neighbors
            pNode.next = newNode;
            nNode.prev = newNode;

            // check if we hit size, increase size and break
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