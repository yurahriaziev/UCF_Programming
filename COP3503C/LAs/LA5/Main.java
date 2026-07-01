package COP3503C.LAs.LA5;

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
				newNode.down = curNode;
				curNode.up = newNode;
			}

			if (i == size) {
				node newLevel = buildLevel(size);
				levels.add(newLevel);
				connectLastLevel();
				BL.add(newLevel);
			}

			node pNode = BL.get(i);
			node nNode = pNode.next;

			newNode.next = nNode;
			newNode.prev = pNode;

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
	
	// Deletes value from the list. Returns true if value was in the list and was deleted.
	// Returns false if value wasn't in the list and takes no action.
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
	
	// Returns the number of items on the top level.
	private int topLevelSize() {
		node cur = levels.get(size-1);
		int sz = 0;
		while (cur != null) {
			cur = cur.next;
			sz++;
		}
		return sz;
	}
	
	// Connects the last level to the rest of the lists.
	public void connectLastLevel() {
		
		// We can obtain both of these.
		node top = levels.get(levels.size()-1);
		node below = levels.get(levels.size()-2);
		
		// Link left sides up and down.
		top.down = below;
		below.up = top;
		
		// End of top list.
		top = top.next;
		
		// Go to end of second to top list.
		while (below.data != POS_INF) below = below.next;
		
		// Link right sides up and down.
		top.down = below;
		below.up = top;
	}
	
	// For debugging.
	public void printAllLevels() {
		System.out.println(levels.size()+" and "+size);
		for (int i=0; i<size; i++) {
			System.out.print("Level "+i+": ");
			printLevel(i);
		}
		System.out.println("---------------------------");
	}
	
	// Prints level id. For debugging.
	public void printLevel(int id) {
		node cur = levels.get(id);
		while (cur != null) {
			System.out.print(cur.data+" ");
			cur = cur.next;
		}
		System.out.println();
	}
	
	public static void runExperiment(int testSize) {
		int insertNums[] = new int[testSize];
		int deleteNums[] = new int[testSize];

		for (int i=0; i<testSize; i++) {
			insertNums[i] = rndObj.nextInt(2000001);
			deleteNums[i] = rndObj.nextInt(2000001);
		}

		Main skipList = new Main();

		long start = System.currentTimeMillis();

		for (int i=0; i<testSize; i++) {
			skipList.insert(insertNums[i]);
		}

		long end = System.currentTimeMillis();
		long skipInsertTime = end - start;

		start = System.currentTimeMillis();

		for (int i=0; i<testSize; i++) {
			skipList.delete(deleteNums[i]);
		}

		end = System.currentTimeMillis();
		long skipDeleteTime = end - start;
		long skipTotalTime = skipInsertTime + skipDeleteTime;

		TreeSet<Integer> treeSet = new TreeSet<Integer>();

		start = System.currentTimeMillis();

		for (int i=0; i<testSize; i++) {
			treeSet.add(insertNums[i]);
		}

		end = System.currentTimeMillis();
		long treeInsertTime = end - start;

		start = System.currentTimeMillis();

		for (int i=0; i<testSize; i++) {
			treeSet.remove(deleteNums[i]);
		}

		end = System.currentTimeMillis();
		long treeDeleteTime = end - start;
		long treeTotalTime = treeInsertTime + treeDeleteTime;

		System.out.println("Test size: " + testSize);
		System.out.println("=======");
		System.out.println();
		System.out.println("Skip list insertion took " + skipInsertTime + " ms.");
		System.out.println("Skip list deletion took " + skipDeleteTime + " ms.");
		System.out.println("Skip list actions took " + skipTotalTime + " ms.");
		System.out.println("tree set insertion took " + treeInsertTime + " ms.");
		System.out.println("tree set deletion took " + treeDeleteTime + " ms.");
		System.out.println("tree set actions took " + treeTotalTime + " ms.");
		System.out.println();
	}

	public static void main(String[] args) {
		int testSizes[] = {50000, 100000, 150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000};

		for (int i=0; i<testSizes.length; i++) {
			runExperiment(testSizes[i]);
		}
	}
}

class node {

	public int data;
  	public node next, prev, up, down;
	public int level;
  
	// public node next;
	// public node prev;
	// public node up;
	// public node down;
	// public int level;

	public node(int myval, int mylev) {
		data = myval;
		level = mylev;
		next = null;
		prev = null;
		up = null;
		down = null;
	}

}