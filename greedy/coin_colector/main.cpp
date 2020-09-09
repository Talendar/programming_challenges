/**
 * Greedy solution for the coin collector problem, available at: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2231
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
using namespace std;


int solve(vector<int> coins) 
{   
    int count = 2;  // using the smallest and the biggest coin in every case
    int sum = coins[0];

    for(int i = 1; i < ((int) coins.size() - 1); i++) {
        int c = coins[i];

        if((sum + c) < coins[i+1]) {
            sum += c;
            count++;
        }
    }

    return count;
}


int main() 
{
    int num_tests;  cin >> num_tests;
    for(int t = 0; t < num_tests; t++) {
        int coin_types;  cin >> coin_types;
        vector<int> coins(coin_types);

        for(int i = 0; i < coin_types; i++) {
            cin >> coins[i];
        }

        printf("%d\n", solve(coins));
    }

    return 0;
}