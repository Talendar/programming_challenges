/**
 * UVA - PROBLEM 12747 (https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=4600)
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;


int solve(vector<int> v)
{
    vector<int> memo;
    memo.push_back(v[0]);

    for(int i = 1; i < (int) v.size(); i++) {
        int pos = 0;
        while(memo[pos] < v[i] && ++pos < (int) memo.size());  // find the first element in memo greater than v[i]
        
        if(pos == (int) memo.size())
            memo.push_back(v[i]);
        else
            memo[pos] = v[i];
    }

    return memo.size();
}


int main()
{
    int tests;  cin >> tests;
    for(int t = 1; t <= tests; t++) {
        int n;  cin >> n;
        vector<int> v1(2*n), v2(2*n);

        for(int i = 0; i < n; i++) {
            int j;  cin >> j;
            v1[j] = i;
        }

        for(int i = 0; i < n; i++) {
            int j;  cin >> j;
            v2[i] = v1[j];
        }
        
        printf("Case %d: %d\n", t, (n - solve(v2)) * 2);
    }
}