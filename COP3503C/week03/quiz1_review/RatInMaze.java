package COP3503C.week03.quiz1_review;

public class RatInMaze {
    static int N;

    void printSolution(int sol[][]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                System.out.print(" " + sol[i][j] + " ");
            System.out.println();
        }
    }

    boolean isSafe(int maze[][], int x, int y) {
        if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1) {
            return true;
        }

        return false;
    }

    boolean solveMaze(int maze[][]) {
        int sol[][] = new int[N][N];

        if (solveMazeUtil(maze, 0, 0, sol) == false) {
            System.out.println("Solution does not exist");
            return false;
        }

        printSolution(sol);
        return true;
    }

    boolean solveMazeUtil(int maze[][], int x, int y, int sol[][]) {
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

    public static void main(String[] args) {
        RatInMaze rat = new RatInMaze();

        int maze1[][] = {
            {1, 0, 0, 1},
            {1, 1, 0, 0},
            {1, 1, 1, 1},
            {0, 1, 1, 1}
        };
        int maze2[][] = {
            {1, 0, 0, 1},
            {1, 1, 0, 0},
            {1, 1, 1, 1},
            {1, 1, 1, 1}
        };
        N = maze1.length;
        System.out.println("Solution for Maze 1:");
        rat.solveMaze(maze1);
        System.out.println("\nSolution for Maze 2:");
        rat.solveMaze(maze2);
    }
}
