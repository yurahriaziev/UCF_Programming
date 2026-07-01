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
        node top = levels.get(size-1);
        int topSize = 0;
        while (top.next.data != POS_INF) {
            topSize++;
            top = top.next;
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

    public boolean delete(int value) {
        ArrayList<node> BL = search(value);

        node bottom = BL.get(0);
        if (bottom.next.data != value) {
            return false;
        }

        node curNode = bottom.next;
        while (curNode != null) {
            node pNode = curNode.prev;
            node nNode = curNode.next;

            pNode.next = nNode;
            nNode.prev = pNode;

            curNode = curNode.up;
        }

        if (size > 1 && topLevelSize() == 2) {
            levels.remove(size-1);
            size--;
        }

        return true;
    }

    public boolean insert(int value) {
        ArrayList<node> BL = search(value);

        if (BL.get(0).next.data == value) {
            return false;
        }

        node curNode = null;
        int i = 0;
        while (i <= size) {
            int coin;
            if (i == 0) {
                coin = 1;
            } else {
                coin = rndObj.nextInt(2);
            }

            if (coin == 0) {
                break;
            }

            node newNode = new node(value, i);
            if (i > 0) {
                curNode.up = newNode;
                newNode.down = curNode;
            }

            if (i == size) {
                node newLevel = buildLevel(size);
                levels.add(newLevel);
                connectLastLevel();
                BL.add(newLevel);
            }

            node pNode = BL.get(i);
            node nNode = pNode.next;

            newNode.prev = pNode;
            newNode.next = nNode;

            pNode.next = newNode;
            nNode.prev = newNode;

            if (i == size) {
                size++;
                break;
            }

            i++;
            curNode = newNode;
        }

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