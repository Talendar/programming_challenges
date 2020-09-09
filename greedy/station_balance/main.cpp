/**
 * Greedy solution for the station balance problem, available at: https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=351
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{
    int set = 1, num_chambers;
    while(cin >> num_chambers) {
        int num_specimens;  cin >> num_specimens;
        vector<int> masses(2 * num_chambers, 0);

        int total_mass = 0;
        for(int i = 0; i < num_specimens; i++) {
            cin >> masses[i];
            total_mass += masses[i];
        }
        double avg_mass = (double) total_mass / num_chambers;

        sort(masses.begin(), masses.end());
        printf("Set #%d\n", set++);
        
        double imbalance = 0;
        for(int i = 0; i < num_chambers; i++) {
            printf(" %d:", i);
            int chamber_mass = 0;

            if(masses[i] != 0) {
                printf(" %d", masses[i]);
                chamber_mass += masses[i];
            }
            
            int idx = 2*num_chambers - i - 1;
            if(masses[idx] != 0) {
                printf(" %d", masses[idx]);
                chamber_mass += masses[idx];
            }
            
            imbalance += abs(chamber_mass - avg_mass);
            printf("\n");
        }

        printf("IMBALANCE = %.5lf\n\n", imbalance);
    }

    return 0;
}