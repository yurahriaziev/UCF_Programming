package COP3503C.week07;

public class RatInMaze {
    static int N;

    // printSolution: function that will print the solution matrix
    void printSolution(int sol[][]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                System.out.print(" " + sol[i][j] + " ");
            System.out.println();
        }
    }

    // isSafe: function that will check a given (x, y) square if it is safe to go there
    boolean isSafe(int maze[][], int x, int y) {
        if (x>=0 && x<N && y>=0 && y<N && maze[x][y] == 1) {
            return true;
        }

        return false;
    }

    // solveMaze: wrapper function to solve the maze
    boolean solveMaze(int maze[][]) {
        int sol[][] = new int[N][N];

        if (solveMazeUtil(maze, 0, 0, maze) == false) {
            System.out.println("Solution does not exist");
            return false;
        }

        printSolution(sol);
        return true;
    }

    // solveMazeUtil: function that will solve the maze using backtracking
    boolean solveMazeUtil(int maze[][], int x, int y, int sol[][]) {
        if (x == N-1 && y == N-1) {
            sol[x][y] = 1;
            return true;
        }

        if (isSafe(maze, x, y) && sol[x][y] != 1) {
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

    public static void main(String[] args) {
        RatInMaze rat = new RatInMaze();

        int maze1[][] = {
            {1, 0, 0, 1},
            {1, 1, 0, 0},
            {1, 1, 1, 1},
            {0, 1, 1, 1}
        };

        N = maze1.length;
        System.out.println("Maze 1:");
        rat.printSolution(maze1);
        System.out.println("Solution for maze 1:");
        rat.solveMaze(maze1);
    }
}
