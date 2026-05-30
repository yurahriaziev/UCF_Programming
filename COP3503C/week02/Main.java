package COP3503C.week02;

public class Main {
    // Size of the maze
    static int N;
    /* A utility function to print
    solution matrix sol[N][N] */
    void printSolution(int sol[][]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                System.out.print(
                    " " + sol[i][j] + " ");
            System.out.println();
        }
    }
    /* A utility function to check
    if x, y is valid index for N*N maze */
    boolean isSafe(int maze[][], int x, int y) {
        //to be done in the class
        if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1) {
            return true;
        }

        return false;
    }

    boolean solveMaze(int maze[][]) {
        int sol[][] = new int[N][N];
        if (solveMazeUtil(maze, 0, 0, sol) == false) {
            System.out.print("Solution doesn't exist");
            return false;
        }
        printSolution(sol);
        return true;
    }

    /* A recursive utility function to solve Maze
    problem */
    boolean solveMazeUtil(int maze[][], int x, int y, int sol[][]) {
        // runtime: O(2^(n^2))
        //to do in the class
        if (x == N-1 && y == N-1) {
            sol[x][y] = 1;
            return true;
        }

        
        if (isSafe(maze, x, y) == true) {
            if (sol[x][y] == 1) {
                return false;
            }
            sol[x][y] = 1;

            if (solveMazeUtil(maze, x+1, y, sol) == true) {
                return true;
            }

            if (solveMazeUtil(maze, x, y+1, sol) == true) {
                return true;
            }

            sol[x][y] = 0;
            return false;
        }

        return false;
    }

    public static void main(String args[]) {
        Main rat = new Main();
        int maze[][] = {
                { 1, 0, 1, 1, 1 },
                { 1, 1, 1, 0, 1 },
                { 1, 0, 0, 0, 1 },
                { 1, 1, 0, 0, 1 },
                { 0, 1, 1, 1, 1 }
            };
        // int maze[][] = {
        // { 1, 0, 0, 1 },
        // { 1, 1, 0, 0 },
        // { 1, 1, 1, 1 },
        // { 1, 1, 1, 1 }
        // };
        N = maze.length;
        rat.solveMaze(maze);
    }
}
