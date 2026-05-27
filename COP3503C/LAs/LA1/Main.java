/*              COP 3503C Lab 1
This program is written by: Yurii Hriaziev */

package COP3503C.LAs.LA1;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int len = input.nextInt();

        PriorityQueue<Integer> leftMaxHeap = new PriorityQueue<>(Collections.reverseOrder());
        PriorityQueue<Integer> rightMinHeap = new PriorityQueue<>();

        for (int i=0; i<len; i++) {
            double median = 0;

            int numInput = input.nextInt();
            if (leftMaxHeap.size() == 0 || numInput <= leftMaxHeap.peek()) {
                leftMaxHeap.add(numInput);
            } else {
                rightMinHeap.add(numInput);
            }

            // size balancing
            if (leftMaxHeap.size() > rightMinHeap.size() + 1) {
                rightMinHeap.add(leftMaxHeap.poll());
            } else if (rightMinHeap.size() > leftMaxHeap.size() + 1) {
                leftMaxHeap.add(rightMinHeap.poll());
            }

            if (leftMaxHeap.size() == rightMinHeap.size()) {
                median = (leftMaxHeap.peek() + rightMinHeap.peek()) / 2.0;
            } else if (leftMaxHeap.size() > rightMinHeap.size()) {
                median = leftMaxHeap.peek();
            } else {
                median = rightMinHeap.peek();
            }

            System.out.println(median);
        }
    }
}