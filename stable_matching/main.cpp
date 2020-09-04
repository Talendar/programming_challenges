/**
 * Solution for the Stable Marriage Problem (https://www.codechef.com/problems/STABLEMP).
 * @author Gabriel Nogueira (Talendar)
 */


#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;


typedef struct {
    int partner = -1;
    vector <int> pref_list;

    bool is_single() {
        return (partner == -1);
    }
} Person;


//////////////////////// GLOBAL ////////////////////////
Person *men, *women;
int num_marriages;
////////////////////////////////////////////////////////


void marry(int mi, int wi) {
    if(!women[wi].is_single())
        men[women[wi].partner].partner = -1;

    men[mi].partner = wi;
    women[wi].partner = mi;
}


bool try_marry(int mi, int wi) 
{
    if(women[wi].is_single()) {
        marry(mi, wi);
        return true;
    }
    
    for(int i = 0; i < num_marriages; i++) {
        if(women[wi].pref_list[i] == women[wi].partner)
            return false;
        
        if(women[wi].pref_list[i] == mi)
            break;
    }

    marry(mi, wi);
    return true;
}


void solve() 
{
    bool has_single;
    do {
        has_single = false;

        for(int mi = 0; mi < num_marriages; mi++) {
            if(men[mi].is_single()) {
                int wi = men[mi].pref_list[0];
                men[mi].pref_list.erase(men[mi].pref_list.begin());

                try_marry(mi, wi);
                has_single = true;
            }
        }
    } while(has_single);

    for(int i = 0; i < num_marriages; i++)
        printf("%d %d\n", i+1, men[i].partner+1);
}


int main() 
{   
    int num_tests;  cin >> num_tests;
    for(int t = 0; t < num_tests; t++) {
        cin >> num_marriages;

        women = new Person[num_marriages];
        men = new Person[num_marriages];

        // women
        for(int i = 0; i < num_marriages; i++) {
            int w;  cin >> w;  w--;

            for(int j = 0; j < num_marriages; j++) {
                int m;  cin >> m;  m--;
                women[w].pref_list.push_back(m);
            }
        }

        // men
        for(int i = 0; i < num_marriages; i++) {
            int m;  cin >> m;  m--;

            for(int j = 0; j < num_marriages; j++) {
                int w;  cin >> w;  w--;
                men[m].pref_list.push_back(w);
            }
        }

        // solving
        solve();

        // freeing memory
        delete [] women;
        delete [] men;
    }

    return 0;
}