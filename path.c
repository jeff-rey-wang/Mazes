/*
 Jeffrey Wang
 wangw115
 400196865
 path.c
 */
#include <stdio.h>

int find_path(int n, int m, int A[], int i, int j, int k, int l, int path [][2])
{
    // Starting or ending element is '1', ignore path
    if (A[(i * m) + j] == 1 || A[(k * m) + l] == 1)
    {
        return -1;
    }
    // Starting row index isn't within bounds
    else if (i < 0 || i >= n)
    {
        return -2;
    }
    // Starting column index isn't within bounds
    else if (j < 0 || j >= m)
    {
        return -3;
    }
    // Search for path
    else
    {
        // First pair of indices are for starting position
        int pathLength = 0, row = i, column = j;
        path[0][0] = row;
        path[0][1] = column;
        A[row * m + column] = 9;
        // Search while the ending position indices are not in the array
        while (path[pathLength][0] != k || path[pathLength][1] != l)
        {
            char direction = 'N';;
            switch(direction)
            {
                // Move north
                case 'N':
                    // index within range and upper element is 0
                    if (row > 0 && A[(row - 1) * m + column] == 0)
                    {
                        // Increase length
                        pathLength++;
                        // Perform shift
                        row--;
                        // Save indices
                        path[pathLength][0] = row;
                        path[pathLength][1] = column;
                        // Mark the element being moved to
                        A[row * m + column] = 9;
                        break;
                    }
                    // North move is invalid, check East element
                    direction = 'E';
                // Move east
                case 'E':
                    if (column < (m - 1) && A[row * m + (column + 1)] == 0)
                    {
                        pathLength++;
                        column++;
                        path[pathLength][0] = row;
                        path[pathLength][1] = column;
                        A[row * m + column] = 9;
                        break;
                    }
                    direction = 'S';
                // Move south
                case 'S':
                    if (row < (n - 1) && A[(row + 1) * m + column] == 0)
                    {
                        pathLength++;
                        row++;
                        path[pathLength][0] = row;
                        path[pathLength][1] = column;
                        A[row * m + column] = 9;
                        break;
                    }
                    direction = 'W';
                // Move west
                case 'W':
                    if (column > 0 && A[row * m + (column - 1)] == 0)
                    {
                        pathLength++;
                        column--;
                        path[pathLength][0] = row;
                        path[pathLength][1] = column;
                        A[row * m + column] = 9;
                        break;
                    }
                // Move is impossible, move to previous position or give up
                default:
                    // No path is possible
                    if (pathLength == 0)
                    {
                        // Revert changes made to matrix
                        for (int index = 0; index < n*m; index++)
                        {
                            if (A[index] == 9)
                            {
                                A[index] = 0;
                            }
                        }
                        return 0;
                    }
                    // Move to previous position
                    else
                    {
                        // Overwrite indices with invalid indices (-1,-1)
                        path[pathLength][0] = -1;
                        path[pathLength][1] = -1;
                        // Reduce length and take previous position
                        pathLength--;
                        row = path[pathLength][0];
                        column = path[pathLength][1];
                    }
            }
        }
        // Path found, return length of path
        // Revert changes made to matrix
        for (int index = 0; index < n*m; index++)
        {
            if (A[index] == 9)
            {
                A[index] = 0;
            }
        }
        return pathLength + 1;
    }
}
