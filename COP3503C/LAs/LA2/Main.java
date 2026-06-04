/*              COP 3503C Lab 2
This program is written by: Yurii Hriaziev */

package COP3503C.LAs.LA2;
import java.util.*;

public class Main {
    static int N;
    static int square[][];
    static boolean used[];
    static int magicConst;

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        N = input.nextInt();
        magicConst = N * (N * N + 1) / 2;

        square = new int[N][N];
        used = new boolean[N * N + 1];

        System.out.println("N = " + N);

        solveMagicSquare(0, 0);

        input.close();
    }

    static void printSquare() {
        System.out.println("Done!!");
        for (int i=0; i<N; i++) {
            System.out.print("[");
            for (int j=0; j<N; j++) {
                System.out.print(square[i][j]);
                if (j < N - 1) {
                    System.out.print(", ");
                }
            }
            System.out.println("]");
        }
    }

    // backtrack: function that will begin the entire process by filling out a single square in table at a time
    static void solveMagicSquare(int row, int col) {
        if (row == N) {
            if (isMagicSquare()) {
                printSquare();
            }
            return;
        }

        int nextRow = row;
        int nextCol = col + 1;

        if (nextCol == N) {
            nextRow += 1;
            nextCol = 0;
        }

        for (int i=1; i<=N*N; i++) {
            if (used[i] == false) {
                square[row][col] = i;
                used[i] = true;

                if (isSafe(row, col)) {
                    solveMagicSquare(nextRow, nextCol);
                }

                square[row][col] = 0;
                used[i] = false;
            }
        }
    }

    // isMagicSquare: function that checks if the entire N*N grid is a magic square
    static boolean isMagicSquare() {
        int sum;

        for (int i=0; i<N; i++) {
            sum = 0;

            for (int j=0; j<N; j++) {
                sum += square[i][j];
            }
            if (sum != magicConst) {
                return false;
            }
        }

        for (int j=0; j<N; j++) {
            sum = 0;

            for (int i=0; i<N; i++) {
                sum += square[i][j];
            }
            if (sum != magicConst) {
                return false;
            }
        }

        sum = 0;
        for (int i=0; i<N; i++) {
            sum += square[i][i];
        }
        if (sum != magicConst) {
            return false;
        }

        sum = 0;
        for (int i=0; i<N; i++) {
            sum += square[i][N - 1 - i];
        }
        if (sum != magicConst) {
            return false;
        }

        return true;
    }

    static boolean isSafe(int row, int col) {
        if (row >= 0 && row < N && col >= 0 && col < N) {
            return true;
        }

        return false;
    }
}
