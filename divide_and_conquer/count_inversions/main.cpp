/**
 * O(nlogn) solution for the inversion counting problem.
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <queue>
using namespace std;


/**
 * Merges the two sub-arrays and count the number of inversions.
 */
int merge_and_count(int *v, int s, int e, int mid) 
{
    int count = 0;
    queue<int> temp;

    int i = s, j = mid + 1;
    while(i <= mid || j <= e) {
        if(i <= mid) {
            if(v[i] <= v[j] || j > e) {
                temp.push(v[i++]);
                continue;
            }
            count += (mid - i + 1);
        }
        temp.push(v[j++]);
    }

    for(i = s; i <= e; i++) {
        v[i] = temp.front();
        temp.pop();
    }

    return count;
}


/**
 * Merge sort.
 */
int solve(int *v, int s, int e) {
    if(s >= e) return 0;        // base case: only one element left
    int mid = (s + e) / 2;
    return solve(v, s, mid) + solve(v, mid + 1, e) + merge_and_count(v, s, e, mid);
}


int main()
{   
    int num_tests;  cin >> num_tests;
    for(int t = 0; t < num_tests; t++) {
        int count;  cin >> count;

        int values[count];
        for(int i = 0; i < count; i++) {
            cin >> values[i];
        }

        printf("%d\n", solve(values, 0, count - 1));
    }
    
    return 0;
}