package COP3503C.week09;

import java.util.*;

public class CountingMoneyGreAlg {
    static int deno[] = {1, 5, 10, 25, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    static int n = deno.length;

    static void findMin(int r) {
        ArrayList<Integer> ans = new ArrayList<>();

        for (int i=n-1; i>=0; i--) {
            int temp = deno[i];
            while (r >= temp) {
                ans.add(temp);
                r -= temp;
            }
        }

        for (int i = 0; i < ans.size(); i++) {
            int cur = ans.get(i);
            if (cur >= 100) {
                System.out.print("$" + cur / 100 + ", ");
            } else {
                System.out.print(cur + " cents, ");
            }
        }
    }

    public static void main(String[] args) {
        double n1 = 6.39;
        int n = (int)(n1 * 100);

        System.out.println("Min number of change for $" + n1 + ": ");

        // call function to find min coin amount
        findMin(n);
    }
}
