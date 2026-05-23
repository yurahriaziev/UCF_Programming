package COP3503C.week01;

import java.util.*;

public class MainArrayList {
    public static void main(String[] args) {
        ArrayList<Integer> myList = new ArrayList<Integer>();

        myList.add(10);
        myList.add(5);
        myList.add(16);
        myList.add(25);

        myList.add(2, 35);

        System.out.println(myList);

        Integer val = myList.get(3);
        System.out.println(val);

        for (Object i : myList) {
            System.out.println(i);
        }

        System.out.println();

        Iterator<Integer> iter = myList.iterator();
        while (iter.hasNext()) {
            int curval = iter.next();
            if (curval % 2 == 0) {
                iter.remove();
            }
        }

        System.out.println(myList);
    }
}
