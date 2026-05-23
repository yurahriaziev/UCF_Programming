/*              COP 3503C Assignment 1
This program is written by: Yurii Hriaziev */

package COP3503C.PAs.PA1;

import java.util.*;

// Pair: a class that will hold the result of pair lookup
class Pair{
    int n1, n2;

    Pair(int n1, int n2) {
        this.n1 = n1;
        this.n2 = n2;
    }
}
public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int k = input.nextInt();

        for (int i=1; i<=k; i++) {
            int sorted = input.nextInt();
            int n = input.nextInt();

            int A[] = new int[n];

            for (int j=0; j<n; j++) {
                A[j] = input.nextInt();
            }

            int target = input.nextInt();

            Pair res;

            // check if current list is sorted or no to know which function to use (sorted or unsorted)
            if (sorted == 1) {
                res = getCandidatePair(A, target);
            } else {
                res = getCandidatePairUnsorted(A, target);
            }

            if (res.n1 == 0 && res.n2 == 0) {
                System.out.println("Test case#" + i + ": No way you can spend exactly " + target + " points.");
            } else {
                System.out.println("Test case#" + i + ": Spend " + target + " points by playing the games with " + res.n1 + " points and " + res.n2 + " points.");
            }
        }

        input.close();
    }

    // getCandidatePair: function to find a pair that sums up to target in an array
    // using two trackers
    static Pair getCandidatePair(int A[], int target) {
        int left = 0;
        int right = A.length - 1;

        while (left < right) {
            int sum = A[left] + A[right];

            if (sum == target) {
                return new Pair(A[left], A[right]);
            }

            if (sum < target) {
                left++;
            } else {
                right--;
            }
        }

        return new Pair(0, 0);
    }

    // getCandidatePairUnsorted: function that uses HashSet of Integers to store the values, locate values, and compare values
    // to find a pair that add up to given target in O(n) runtime
    static Pair getCandidatePairUnsorted(int A[], int target) {
        HashSet<Integer> seen = new HashSet<Integer>();

        for (int i=0; i<A.length; i++) {
            int diff = target - A[i];

            if (seen.contains(diff)) {
                if (diff < A[i]) {
                    return new Pair(diff, A[i]);
                } else {
                    return new Pair(A[i], diff);
                }
            }

            seen.add(A[i]);
        }

        return new Pair(0, 0);
    }
}
