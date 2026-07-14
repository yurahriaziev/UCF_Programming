package COP3503C.week09;

import java.util.*;

// 1. make node for each char and its freq and left and right children also that class
class HuffmanNode {
    int freq;
    char c;

    HuffmanNode left;
    HuffmanNode right;
}

// 2. comparator class which will help compare nodes
class MyComparator implements Comparator<HuffmanNode> {
    public int compare(HuffmanNode x, HuffmanNode y) {
        return x.freq - y.freq;
    }
}

public class Huffman {
    // PRE ORDER TRAVERSAL
    static void printCode(HuffmanNode root, String s) {
        // base case
        if (root.left == null && root.right == null && Character.isLetter(root.c)) {
            // c is the character in the node
            System.out.println(root.c + ":" + s);

            return;
        }

        printCode(root.left, s + "0");
        printCode(root.right, s + "1");
    }

    public static void main(String[] args) {
        // number of chars
        int n = 6;
        char[] charArray = {'a', 'b', 'c', 'd', 'e', 'f'};
        int[] charFreq = {5, 9, 12, 13, 16, 45};

        // create min heap priority queue q with n values and custom comparator class
        PriorityQueue<HuffmanNode> q = new PriorityQueue<HuffmanNode>(n, new MyComparator());

        // loop for every char and freq and create a HuffmanNode object and add it to queue
        for (int i=0; i<n; i++) {
            HuffmanNode node = new HuffmanNode();
            node.c = charArray[i];
            node.freq = charFreq[i];
            node.left = null;
            node.right = null;

            q.add(node);
        }

        // create null root
        HuffmanNode root = null;

        // extract the two min value from queue until size of queue i 1
        while (q.size() > 1) {
            // first min extract
            HuffmanNode x = q.poll();

            // second min extract
            HuffmanNode y = q.poll();

            // create a new root node with freq = sum of prev 2 freq and left right nodes respectively
            HuffmanNode f = new HuffmanNode();

            f.freq = x.freq + y.freq;
            f.left = x;
            f.right = y;
            // put char in f's char for asthetics
            f.c = '*'; 

            // mark the new root as the overall root
            root = f;

            // add new root to min-heap
            q.add(f);
        }
    }
}
