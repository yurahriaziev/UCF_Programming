

import java.util.*;

/*              COP 3503C Assignment 4
This program is written by: Yurii Hriaziev */

public class Main {
    static int r;
    static int c;
    static char maze[][];
    static int dist[][];
    static ArrayList<Location> teleports[];
    static boolean usedTeleports[];

    // main function to collect input and run everything
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        r = input.nextInt();
        c = input.nextInt();

        maze = new char[r][c];
        dist = new int[r][c];
        teleports = new ArrayList[26];
        usedTeleports = new boolean[26];

        for (int i=0; i<26; i++) {
            teleports[i] = new ArrayList<Location>();
        }

        int startRow = -1;
        int startCol = -1;
        int endRow = -1;
        int endCol = -1;

        for (int i=0; i<r; i++) {
            String line = input.next();

            for (int j=0; j<c; j++) {
                maze[i][j] = line.charAt(j);

                if (maze[i][j] == '*') {
                    startRow = i;
                    startCol = j;
                } else if (maze[i][j] == '$') {
                    endRow = i;
                    endCol = j;
                } else if (maze[i][j] >= 'A' && maze[i][j] <= 'Z') {
                    int index = maze[i][j] - 'A';
                    teleports[index].add(new Location(i, j));
                }
            }
        }

        int ans = bfs(startRow, startCol, endRow, endCol);

        if (ans == -1) {
            System.out.println("Call 911");
        } else {
            System.out.println(ans);
        }

        input.close();
    }

    // bfs: function that will find the fewest moves from start to end
    static int bfs(int startRow, int startCol, int endRow, int endCol) {
        for (int i=0; i<r; i++) {
            Arrays.fill(dist[i], -1);
        }

        LinkedList<Location> q = new LinkedList<Location>();

        dist[startRow][startCol] = 0;
        q.add(new Location(startRow, startCol));

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (q.size() > 0) {
            Location cur = q.poll();
            if (cur.row == endRow && cur.col == endCol) {
                return dist[cur.row][cur.col];
            }

            for (int i=0; i<4; i++) {
                int nextRow = cur.row + dr[i];
                int nextCol = cur.col + dc[i];

                if (isValid(nextRow, nextCol) == true) {
                    dist[nextRow][nextCol] = dist[cur.row][cur.col] + 1;
                    q.add(new Location(nextRow, nextCol));
                }
            }

            if (maze[cur.row][cur.col] >= 'A' && maze[cur.row][cur.col] <= 'Z') {
                int index = maze[cur.row][cur.col] - 'A';

                if (usedTeleports[index] == false) {
                    usedTeleports[index] = true;

                    for (int i=0; i<teleports[index].size(); i++) {
                        Location next = teleports[index].get(i);

                        if (dist[next.row][next.col] == -1) {
                            dist[next.row][next.col] = dist[cur.row][cur.col] + 1;
                            q.add(next);
                        }
                    }
                }
            }
        }

        return -1;
    }

    // isValid: function that will check if a given row and col postion is safe to move to and have not been seen
    static boolean isValid(int row, int col) {
        if (row < 0 || row >= r || col < 0 || col >= c) {
            return false;
        }

        if (maze[row][col] == '!') {
            return false;
        }

        if (dist[row][col] != -1) {
            return false;
        }

        return true;
    }
}

// this class will store a location of a row and col in a maze
class Location {
    int row;
    int col;

    public Location(int row, int col) {
        this.row = row;
        this.col = col;
    }
}
