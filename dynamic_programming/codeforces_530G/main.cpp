/**
 * CodeForces - PROBLEM 530G (https://codeforces.com/problemset/problem/530/G)
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;


/**
 * Cost of removing/inserting a character.
 */
int ins_rmv_cost(char c) {
    return c - 'a' + 1;
}


/**
 * Cost of replacing a character by another one.
 */
int replace_cost(char a, char b) {
    return abs(a - b);
}


/**
 * Solves the problem using a naive recursive approach.
 */
int edit_dist_rec(string s1, string s2, int m, int n) 
{
    // insert all remaining chars of s2 into s1
    if(m == 0) {  
        int cost = 0;
        for(int i = 0; i < n; i++)
            cost += ins_rmv_cost(s2[i]);
        return cost;
    }
    
    // remove all remaining chars of s1
    if(n == 0) {
        int cost = 0;
        for(int i = 0; i < m; i++)
            cost += ins_rmv_cost(s1[i]);
        return cost;
    }

    // last chars are equal
    if(s1[m-1] == s2[n-1])
        return edit_dist_rec(s1, s2, m-1, n-1);
    
    // last chars are different
    return min({
        replace_cost(s1[m-1], s2[n-1]) + edit_dist_rec(s1, s2, m-1, n-1),  // replace
        ins_rmv_cost(s1[m-1]) + edit_dist_rec(s1, s2, m-1, n),             // remove
        ins_rmv_cost(s2[n-1]) + edit_dist_rec(s1, s2, m, n-1)              // insert
    });
}


/**
 * Solves the problem using dynamic programming. 
 */
int edit_dist_dp(string s1, string s2)
{   
    int memo[s1.length() + 1][s2.length() + 1];  memset(memo, 0, sizeof(memo));
    for(unsigned int m = 0; m <= s1.length(); m++) {
        for(unsigned int n = 0; n <= s2.length(); n++) {
            // insert all remaining chars of s2 into s1
            if(m == 0) {  
                for(unsigned int i = 0; i < n; i++)
                    memo[m][n] += ins_rmv_cost(s2[i]);
            }
            
            // remove all remaining chars of s1
            else if(n == 0) {
                for(unsigned int i = 0; i < m; i++)
                    memo[m][n] += ins_rmv_cost(s1[i]);
            }

            // last chars are equal
            else if(s1[m-1] == s2[n-1])
                memo[m][n] = memo[m-1][n-1];
            
            // last chars are different
            else {
                memo[m][n] = min({
                    replace_cost(s1[m-1], s2[n-1]) + memo[m-1][n-1],  // replace
                    ins_rmv_cost(s1[m-1]) + memo[m-1][n],             // remove
                    ins_rmv_cost(s2[n-1]) + memo[m][n-1]              // insert
                });
            } 
        }
    }
    return memo[s1.length()][s2.length()];
}


int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    printf("%d\n", edit_dist_dp(s1, s2));
    return 0;
}