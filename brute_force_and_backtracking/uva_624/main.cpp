/**
 * Brute-force solution for the problem: https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=565
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
using namespace std;

int best_sum, res;
vector<int> solution;


void solve(int i, vector<int>& tracks, int sum, int cur, int N) 
{
    if(sum > N) 
        return;
    
    if(sum > best_sum) {
        best_sum = sum;
        res = cur;
    }

    if(i >= (int) tracks.size()) 
        return;

    solve(i+1, tracks, sum+tracks[i], cur|(1<<i), N);
    solve(i+1, tracks, sum, cur, N);
}

int main()
{
    int N, track_count;
    while(cin >> N) { 
        cin >> track_count;

        vector<int> tracks;
        for(int i=0; i < track_count; i++) {
            int temp;  cin >> temp;
            tracks.push_back(temp);
        }

        best_sum = 0;
        solve(0, tracks, 0, 0, N);

        for(int i=0; i < track_count; i++) {
            if(res & (1<<i)) {
                printf("%d ", tracks[i]);
            }
        }
        printf("sum:%d\n", best_sum);
    }

    return 0;
}