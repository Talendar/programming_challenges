/**
 * UVA - PROBLEM 11368 (https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2353)
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;


/**
 * Defines a doll's attributes and operations.
 */
class Doll {
    public:
    int width, height;

    Doll(int width, int height) {
        this->width = width;
        this->height = height;
    }

    Doll() {
        this->width = this->height = -1;
    }

    bool operator<(Doll &d) {
        return this->width > d.width || (this->width == d.width && this->height < d.height);
    }

    void print() {
        printf("w = %d  |  h = %d\n", this->width, this->height);
    }
};


/**
 *  Searches for the position of the given height in the solution vector using
 * binary search.
 */
int binary_search(vector<int> v, int h) {
    int l = 0, r = (int) v.size() - 1;
    while(l < r) {
        int m = (l + r) / 2;
        if(v[m] <= h) 
            l = m + 1;
        else 
            r = m;
    }

    return l;
}


/**
 *  Solves the problem using dynamic programming. Searches for the Longest 
 * Decreasing Subsequence (LDS).
 */
int solve(vector<Doll> dolls) {
    vector<int> v;
    v.push_back(dolls[0].height);

    for(int i = 1; i < (int) dolls.size(); i++) {
        int pos = binary_search(v, dolls[i].height);
        if(v[pos] > dolls[i].height)
            v[pos] = dolls[i].height;
        else 
            v.push_back(dolls[i].height);
    }

    return (int) v.size();
}


int main() 
{
    int tests;  cin >> tests;
    for(int t = 0; t < tests; t++) {
        int n;  cin >> n;
        vector<Doll> dolls(n);

        for(int i = 0; i < n; i++) 
            cin >> dolls[i].width >> dolls[i].height;

        sort(dolls.begin(), dolls.end());
        printf("%d\n", solve(dolls));
    }

    return 0;
}