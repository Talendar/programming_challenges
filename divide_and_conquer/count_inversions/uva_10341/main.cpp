/**
 * UVA - PROBLEM 10341 (https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1282)
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <vector>
#include <math.h>

#define EPS 0.0000001
using namespace std;


double f(double x, vector<int> params) {
    int p = params[0], q = params[1], r = params[2], s = params[3], t = params[4], u = params[5];
    return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}


double solve(vector<int> params)
{
    if(f(0, params) * f(1, params) > 0)    // checks if at least one root exists
        return -1;

    double l = 0, r = 1;
    while((r - l) > EPS) {
        double c = (l + r) / 2;
        double fc = f(c, params);

        if(f(l, params) * fc <= 0) 
            r = c;
        else
            l = c;
    }

    return l;
}


int main() 
{
    vector<int> params(6);
    while(cin >> params[0]) {
        for(int i = 1; i < 6; i++)
            cin >> params[i];
        
        double x = solve(params);
        if(x == -1) 
            printf("No solution\n");
        else 
            printf("%.4lf\n", x);
    }

    return 0;
}