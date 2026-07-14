package COP3503C.week09;

import java.util.*;

class ItemValue implements Comparable<ItemValue> {
    Double cost;
    double wt, val, ind;

    public ItemValue(int wt, int val, int ind) {
        this.wt = wt;
        this.val = val;
        this.ind = ind;
        cost = Double.valueOf((double)val / (double)wt);
    }

    // compareTo function return negative if first number is smaller, return positive if first number is larger, return 0 if both nums are same
    public int compareTo(ItemValue rhs) {
        return Double.compare(rhs.cost, cost);
    }

    public String toString() {
        return "Cost: " + this.cost + " wt: " + this.wt + "\n";
    }
}

public class FractKnapsackGreAlg {
    static double getMaxValue(int[] wt, int[] val, int capacity) {
        // create list of items
        ItemValue[] itemVals = new ItemValue[wt.length];

        // initialize each item with ItemValue class
        for (int i=0; i<wt.length; i++) {
            itemVals[i] = new ItemValue(wt[i], val[i], i);
        }

        // sort each item's unit price in descending order
        // done automatically with the compareTo function
        Arrays.sort(itemVals);

        // start empty knapsack value
        double totalValue = 0;
        for (ItemValue i : itemVals) {
            // get current weight and value;
            int curWt = (int)i.wt;
            int curVal = (int)i.val;

            // check if we can take the whole thing
            if (capacity - curWt >= 0) {
                capacity -= curWt;
                totalValue += curVal; 
            } else {
                double fraction = ((double)capacity / (double)curWt);
                totalValue += (fraction * curVal);
                capacity -= curWt * fraction;
                // break because we are using the rest of the available space
                break;
            }
        }

        return totalValue;
    }

    public static void main(String[] args) {
        int[] wt = {10, 40, 20, 30};
        int[] val = {60, 40, 100, 120};
        int cap = 50;

        double maxValue = getMaxValue(wt, val, cap);

        System.out.println("Max value we can obtain: " + maxValue);
    }
}
