package COP3503C.week01;

import java.util.*;

class Point implements Comparable<Point>{
    int x, y;
    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public int compareTo(Point rhs) {
        if (this.x == rhs.x) {
            return Integer.compare(this.y, rhs.y);
        }
        return Integer.compare(this.x, rhs.x);
    }

    @Override
    public String toString() {
        return "X = " + this.x + " Y = " + this.y + "\n";
    }
}

public class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        Point[] points = new Point[5];

        for (int i=0; i<5; i++) {
            points[i] = new Point(rand.nextInt(100), rand.nextInt(100));
        }

        for (int i = 0; i < 5; i++) {
            System.out.println(points[i].toString());
        }

        Arrays.sort(points);
        System.out.println("-------------");
        for (int i = 0; i < 5; i++) {
            System.out.println(points[i]);
        }
    }
}
