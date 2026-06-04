package COP3503C.week03.quiz1_review;

public class NQueens {
    public static int N;

    void printSolution(int board[][]) {
        System.out.println("Printing in matrix format: \n");
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                System.out.format(" %d ", board[i][j]);
            }
            System.out.format("\n");
        }

        System.out.format("Printing in Queen format: \n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == 1)
                    System.out.format("Q%d ", i+1);
                // No queen here, so print a blank.
                else
                    System.out.format("_ ");
            }
            System.out.format("\n");
        }
    }

    /* check to see if it is safe to put the queen in x,y position */
    boolean isSafe(int board[][], int x, int y) {
        int XminusY = x - y;
        int XplusY = x + y;

        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                if (i == x || j == y || XminusY == (i - j) || XplusY == (i + j)) {
                    if (board[j][j] == 1) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    boolean isSafeOn(int board[][], int x, int y) {
        // check if same row
        for (int i=0; i<y; i++) {
            if (board[x][i] == 1) {
                return false;
            }
        }
        for (int i=0; i<x; i++) {
            if (board[i][y] == 1) {
                return false;
            }
        }

        for (int i=x, j=y; i>=0 && j>=0; i--, j--) {
            if (board[i][j] == 1) {
                return false;
            }
        }
        
        for (int i=x, j=y; i>=0 && j<N; i--, j++) {
            if (board[i][j] == 1) {
                return false;
            }
        }

        return true;
    }

    /* A recursive utility function to solve N Queen problem */
    boolean solveNQUtil(int n, int row, int board[][]) {
        if (row == N) {
            return true;
        }

        for (int c=0; c<N; c++) {
            if (isSafeOn(board, row, c)) {
                board[row][c] = 1;
                if (solveNQUtil(n, row+1, board)) {
                    return true;
                }
                board[row][c] = 0;
            }
        }

        return false;
    }

    /* This function solves the N Queen problem using Backtracking. */
    public void solveNQ() {
        int[][] board = new int[N][N]; // initialize all positions to 0 by default

        if (solveNQUtil(N, 0, board) == false) {
            System.out.println("Solution does not exist");
            return;
        }

        printSolution(board);
    }
    
    public static void main(String[] args) {
        NQueens m = new NQueens();
        N = 4;
        m.solveNQ();
    }
}
