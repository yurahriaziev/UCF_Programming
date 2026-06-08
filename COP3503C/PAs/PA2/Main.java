package COP3503C.PAs.PA2;


/*              COP 3503C Assignment 2
This program is written by: Yurii Hriaziev */
import java.util.*;

public class Main {
    // variables for the class
    private static int N;
    private static int M;
    private static int S;
    private static char matrix[][];
    private static boolean visited[][];
    private static char res[][];
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        M = input.nextInt();
        N = input.nextInt();
        S = input.nextInt();

        matrix = new char[M][N];
        visited = new boolean[M][N];
        res = new char[M][N];

        for (int i=0; i<M; i++) {
            for (int j=0; j<N; j++) {
                matrix[i][j] = input.next().charAt(0);
            }
        }

        for (int i=0; i<S; i++) {
            String word = input.next();

            System.out.println("Looking for " + word);

            clearRes();
            clearVisited();

            // find the word here
            if (findWord(word) == true) {
                printRes();
            } else {
                System.out.println(word + " not found!\n");
            }
        }

        input.close();
    }

    // findWord: function that received a string 'word' and will look for that word in the
    // matrix in the given direction. If found -> true otherwise -> false
    static boolean findWord(String word) {
        for (int i=0; i<M; i++) {
            for (int j=0; j<N; j++) {
                if (findWordUtil(word, 0, i, j)) {
                    return true;
                }
            }
        }

        return false;
    }

    // findWordUtil: backtracking main working function that will search for a given letter in a given (x,y) box
    static boolean findWordUtil(String word, int index, int x, int y) {
        if (index == word.length()) {
            return true;
        }

        if (isSafe(word, index, x, y) == false) {
            return false;
        }

        visited[x][y] = true;
        res[x][y] = matrix[x][y];

        // going to different directions
        if (findWordUtil(word, index + 1, x, y + 1) == true) {
            return true;
        }

        if (findWordUtil(word, index + 1, x + 1, y) == true) {
            return true;
        }

        if (findWordUtil(word, index + 1, x + 1, y + 1) == true) {
            return true;
        }

        if (findWordUtil(word, index + 1, x + 1, y - 1) == true) {
            return true;
        }

        if (findWordUtil(word, index + 1, x, y - 1) == true) {
            return true;
        }

        if (findWordUtil(word, index + 1, x - 1, y) == true) {
            return true;
        }

        if (findWordUtil(word, index + 1, x - 1, y + 1) == true) {
            return true;
        }

        if (findWordUtil(word, index + 1, x - 1, y - 1) == true) {
            return true;
        }

        // backtracking part
        visited[x][y] = false;
        res[x][y] = ' ';

        return false;
    }

    static boolean isSafe(String word, int index, int row, int col) {
        if (row < 0 || row >= M || col < 0 || col >= N) {
            return false;
        }

        if (visited[row][col] == true) {
            return false;
        }

        if (matrix[row][col] != word.charAt(index)) {
            return false;
        }

        return true;
    }

    // helpers:
    static void clearRes() {
        for (int i=0; i<M; i++) {
            for (int j=0; j<N; j++) {
                res[i][j] = ' ';
            }
        }
    }

    static void clearVisited() {
        for (int i=0; i<M; i++) {
            for (int j=0; j<N; j++) {
                visited[i][j] = false;
            }
        }
    }

    static void printRes() {
        for (int i=0; i<M; i++) {
            System.out.print("[");
            for (int j=0; j<N; j++) {
                System.out.print(res[i][j]);

                if (j < N - 1) {
                    System.out.print(", ");
                }
            }

            System.out.println("]");
        }

        System.out.println();
    }
}
