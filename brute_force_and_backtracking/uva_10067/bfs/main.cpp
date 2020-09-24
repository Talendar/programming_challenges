/**
 * UVA - PROBLEM 10067 (https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1008)
 * Solution using the Breadth-first search algorithm.
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;


vector<int> spin_inc(vector<int> wheel, int i) {
    if(wheel[i] == 9) 
        wheel[i] = 0;
    else 
        wheel[i]++;
    return wheel;
}

vector<int> spin_dec(vector<int> wheel, int i) {
    if(wheel[i] == 0) 
        wheel[i] = 9;
    else 
        wheel[i]--;
    return wheel;
}

int to_int(vector<int> wheel) {
    int num = 0;
    for(int i = 0; i < (int) wheel.size(); i++)
        num += wheel[i] * pow(10, i);
    return num;
}   

bool is_forbidden(int num, vector<int> forbidden) {
    for(int i = 0; i < (int) forbidden.size(); i++) {
        if(num == forbidden[i])
            return true;
    }
    return false;
}

/**
 * Solves the problem using the Breadth-first Search (BFS) algorithm.
 */
int solve(vector<int> start, vector<int> target, vector<int> forbidden)
{   
    vector<int> path_dist(10000, -1);
    path_dist[to_int(start)] = 0;

    queue<vector<int>> q;
    q.push(start);

    while((int) q.size() > 0) {
        vector<int> cur_vec = q.front();  q.pop();
        int cur_num = to_int(cur_vec);

        if(cur_vec == target)
            return path_dist[to_int(target)];

        for(int i = 0; i < (int) cur_vec.size(); i++) {
            vector<int> inc_vec = spin_inc(cur_vec, i);
            int inc_num = to_int(inc_vec);

            if(path_dist[inc_num] == -1 && !is_forbidden(inc_num, forbidden)) {
                path_dist[inc_num] = path_dist[cur_num] + 1;
                q.push(inc_vec);
            }

            vector<int> dec_vec = spin_dec(cur_vec, i);
            int dec_num = to_int(dec_vec);

            if(path_dist[dec_num] == -1 && !is_forbidden(dec_num, forbidden)) {
                path_dist[dec_num] = path_dist[cur_num] + 1;
                q.push(dec_vec);
            }
        }
    }

    return -1;
}

int main()
{
    int tests;  cin >> tests;
    for(int t = 0; t < tests; t++) {
        vector<int> wheel(4);
        for(int i = 0; i < 4; i++)
            cin >> wheel[i];

        vector<int> target(4);
        for(int i = 0; i < 4; i++)
            cin >> target[i];

        int n;  cin >> n;
        vector<int> forbidden(n);
        for(int i = 0; i < n; i++) {
            vector<int> temp(4);
            for(int j = 0; j < 4; j++) {
                cin >> temp[j];
            }
            forbidden[i] = to_int(temp);
        }

        cin.ignore();
        printf("%d\n", solve(wheel, target, forbidden));
    }

    return 0;
}
