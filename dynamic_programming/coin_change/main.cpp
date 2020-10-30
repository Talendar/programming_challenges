/**
 * Solution for the coin problem.
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
using namespace std;


/**
 * Solves the problem using dynamic programming.
 */
int solve_dp(int v, vector<int> &coins, unordered_map<int, int> &memo) 
{
    if(v == 0)
        return 0;

    memo[v] = INT_MAX;
    for(int i = 0; i < (int) coins.size(); i++) {
        int w = v - coins[i];
        if(w >= 0) {
            int s = 1 + (memo.count(w) > 0 ? memo[w] : solve_dp(w, coins, memo));
            memo[v] = min( s, memo[v] );
        }
    }

    return memo[v];
}   


/**
 * Solves the problem using a naive recursive solution.
 */
int solve_naive(int v, vector<int> &coins) 
{
    if(v == 0)
        return 0;

    int min_coins = INT_MAX;
    for(int i = 0; i < (int) coins.size(); i++) {
        if(coins[i] <= v)
            min_coins = min( 1 + solve_naive(v - coins[i], coins), 
                             min_coins );
    }

    return min_coins;
}


int main() 
{
    int n;  cin >> n;
    for(int i = 0; i < n; i++) {
        int v;  cin >> v;
        int q;  cin >> q;

        vector<int> coins(q);
        for(int j = 0; j < q; j++) 
            cin >> coins[j];

        unordered_map<int, int> memo;
        int s = solve_dp(v, coins, memo);

        if(s == INT_MIN)
            printf("sem solucao\n");
        else 
            printf("%d\n", s);
    }

    return 0;
}