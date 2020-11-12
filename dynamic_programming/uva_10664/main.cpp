/**
 * UVA - PROBLEM 10664 (https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1605)
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


/**
 * Solves the problem using dynamic programming.
 */
bool solve_pd(vector<int> weights, int sum)
{
    int n = (int) weights.size();
    bool memo[n + 1][sum + 1];  // memo[i][j] == 1  <===>  there is a subset of weights[0, ..., i] with sum j

    // base case 1: null sum
    for(int i = 0; i <= n; i++) 
        memo[i][0] = true;

    // base case 2: non-null sum & empty subset
    for(int j = 1; j <= sum; j++)
        memo[0][j] = false;

    // bottom-up solving
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= sum; j++) {
            if(weights[i - 1] > j) 
                memo[i][j] = memo[i - 1][j];
            else 
                memo[i][j] = memo[i - 1][j] || memo[i - 1][j - weights[i - 1]];
        }
    }

    return memo[n][sum];
}


/**
 * Solves the problem using simple recursion.
 */
bool solve_rec(vector<int> weights, int sum, int i) 
{
    if(sum == 0)
        return true;

    if(i < 0) 
        return false; 

    return solve_rec(weights, sum - weights[i], i - 1)  // explores the subsets that contain i
             || solve_rec(weights, sum, i - 1);         // explores the subsets that doesn't contain i
}


int main()
{
    int num_tests;  cin >> num_tests;
    string line;  getline(cin, line);  // consumes empty line

    for(int t = 0; t < num_tests; t++) {
        getline(cin, line);
        stringstream ss(line);

        vector<int> weights;
        int sum = 0;
        for(int i = 0; ss >> i; ) {
            weights.push_back(i);
            sum += i;
        }
        
        bool solution = (sum % 2 == 0) ? solve_pd(weights, sum / 2) : false;
        printf("%s\n", (solution) ? "YES" : "NO");
    }

    return 0;
}