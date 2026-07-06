package COP3503C.week08;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        // solving elevator problem
        Scanner stdin = new Scanner(System.in);

        int n = stdin.nextInt();
        int start = stdin.nextInt()-1;
        int end = stdin.nextInt()-1;
        int up = stdin.nextInt();
        int down = stdin.nextInt();

        int dist[] = new int[n];
        Arrays.fill(dist, -1);

        dist[start] = 0;

        LinkedList<Integer> q = new LinkedList<>();
        q.add(start);

        // run BFS
        while (q.size() > 0) {
            // get next item -> deque
            int cur = q.poll();
            if (cur == end) break;

            // check if can go up and we have not visited that floor
            if (cur+up < n && dist[cur+up] == -1) {
                dist[cur+up] = dist[cur] + 1;
                q.add(cur+up);
            }

            // same for down
            if (cur-down >= 0 && dist[cur-down] == -1) {

            }
        }

        if (dist[end] == -1) {
            System.out.println("Use the stairs");
        } else {
            System.out.println(dist[end]);
        }
    }
}
