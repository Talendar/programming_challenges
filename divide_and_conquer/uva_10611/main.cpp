/**
 * UVA - PROBLEM 10611 (https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1552)
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
using namespace std;


/**
 * Solves the problem using binary search.
 */
void solve(vector<int> &v, int h) 
{
    int l = 0, r = v.size() - 1;
    while(r > l) {
        int c = (l + r) / 2;
        if(h == v[c])
            l = r = c;
        else if(h > v[c])
            l = c + 1;
        else 
            r = c - 1;
    }

    if(v[l] >= h)
        while(--l >= 0 && v[l] == h);
    if(l >= 0 && v[l] < h) 
        printf("%d ", v[l]);
    else 
        printf("X ");

    if(v[r] <= h)
        while(++r < (int) v.size() && v[r] == h);
    if(r < (int) v.size() && v[r] > h)
        printf("%d\n", v[r]);
    else 
        printf("X\n");
}


int main()
{
    int n;  cin >> n;
    vector<int> heights(n);
    for(int i = 0; i < n; i++)
        cin >> heights[i];
    
    int q;  cin >> q;
    for(int i = 0; i < q; i++) {
        int h;  cin >> h;
        solve(heights, h);
    }

    return 0;
}