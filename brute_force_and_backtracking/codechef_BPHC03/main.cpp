/**
 * Solution for the problem: https://www.codechef.com/problems/BPHC03
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
using namespace std;

void solve(int i, int j, vector< vector<int> > maze, int *count)
{
    int n = maze.size();
    if(i == n || j == n || i < 0 || j < 0 || maze[i][j] == 1 || maze[i][j] == -1)
        return;

    if(i == (n-1) && j == (n-1))
        (*count)++;

    maze[i][j] = -1;
    solve(i-1, j, maze, count);
    solve(i+1, j, maze, count);
    solve(i, j-1, maze, count);
    solve(i, j+1, maze, count);
}

int main() 
{
    int n; cin >> n;
    vector< vector<int> > maze;

    for(int i = 0; i < n; i++) {
        vector<int> row;
        for(int j = 0; j < n; j++) {
            int t; cin >> t;
            row.push_back(t);
        }
        maze.push_back(row);
    }

    int count = 0;
    solve(0, 0, maze, &count);
    printf("%d\n", count);
}