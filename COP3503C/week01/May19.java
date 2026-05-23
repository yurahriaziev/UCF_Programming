package COP3503C.week01;

import java.util.Arrays;
import java.util.Collections;

public class May19 {
    public static void main(String[] args) {
        int[] a = {6, 5, 8, 3, 20, 15, 7, 14};
        System.out.println("a array: " + Arrays.toString(a));

        int b[];
        b = new int[10];

        Arrays.fill(b, -1);
        System.out.println("b array: " + Arrays.toString(b));
        
        Arrays.fill(b, 2, 6, 0);
        System.out.println("b array: " + Arrays.toString(b));

        Integer[] f = {50, 8, 2, 12, 34, 42};
        Arrays.sort(f, Collections.reverseOrder());
        System.out.println("f array: " + Arrays.toString(f));
    }
}
