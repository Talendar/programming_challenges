/**
 * UVA - PROBLEM 10067 (https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1008)
 * Solution using the A* search algorithm.
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;


enum Spin {INC = 100, DEC = 101};
enum Status {OPEN = 0, VISITED = 1, FORBIDDEN = -1};


class WheelState {
    public:

    int d[4];       // digits
    int depth = 0;  // distance to the origin state
    WheelState() {}

    /**
     * Creates a new state by increasing or decreasing the parent state i-th digit.
     */
    WheelState(WheelState parent, Spin s, int i) {
        for(int c = 0; c < 4; c++) 
            this->d[c] = parent.d[c];
        this->depth = parent.depth + 1;

        if(s == Spin::INC) {
            if(this->d[i] == 9)  this->d[i] = 0;
            else  this->d[i]++;
        }
        else {
            if(this->d[i] == 0)  this->d[i] = 9;
            else  this->d[i]--;
        }
    }

    void set_status(Status status_table[10][10][10][10], Status new_status) {
        status_table[d[0]][d[1]][d[2]][d[3]] = new_status;
    }

    bool is_open(Status status_table[10][10][10][10]) {
        return (status_table[d[0]][d[1]][d[2]][d[3]] == OPEN);
    }

    int dist_to(WheelState w) {
        int dist = 0;
        for(int i = 0; i < 4; i++) {
            int n = abs(this->d[i] - w.d[i]);
            dist += min(n, 10 - n);
        }
        return dist;
    }

    bool operator== (WheelState w) {
        return (this->d[0] == w.d[0] && this->d[1] == w.d[1] &&
                this->d[2] == w.d[2] && this->d[3] == w.d[3]);
    }

    void print() {
        printf("[%d] %d %d %d %d\n", depth, d[0], d[1], d[2], d[3]);
    }
};


/**
 * Used by the priority queue to compare two wheel states. Acts as the evaluation
 * function (f = h + g) for the A* algorithm. 
 */
class StatesComparator {
    public:
    WheelState origin, target;
    StatesComparator(WheelState origin, WheelState target) {
        this->origin = origin;
        this->target = target;
    }

    bool operator() (WheelState w1, WheelState w2) {
        int f1 = w1.depth + w1.dist_to(target);
        int f2 = w2.depth + w2.dist_to(target);
        return f1 > f2;
    }
};


/**
 * Solves the problem using the A* search algorithm.
 */
int solve(WheelState origin, WheelState target, Status status_table[10][10][10][10]) 
{
    priority_queue<WheelState, vector<WheelState>, StatesComparator> pq{StatesComparator(origin, target)};
    pq.push(origin);

    Spin spins[2] = {INC, DEC};
    while(!pq.empty()) {
        WheelState current = pq.top();  pq.pop();
        current.set_status(status_table, VISITED);

        if(current == target)
            return current.depth;

        for(int i = 0; i < 4; i++) {
            for(int s = 0; s < 2; s++) {
                WheelState w(current, spins[s], i);

                if(w.is_open(status_table))
                    pq.push(w);
            }
        }
    }

    return -1;
}


int main()
{
    int tests;  cin >> tests;
    for(int t = 0; t < tests; t++) {
        WheelState origin;
        for(int i = 0; i < 4; i++)
            cin >> origin.d[i];

        WheelState target;
        for(int i = 0; i < 4; i++) 
            cin >> target.d[i];

        Status status_table[10][10][10][10] = {OPEN};
        int num_forbidden;  cin >> num_forbidden;
        for(int i = 0; i < num_forbidden; i++) {
            WheelState fw;
            for(int j = 0; j < 4; j++)
                cin >> fw.d[j];
            fw.set_status(status_table, FORBIDDEN);
        }

        cin.ignore();
        printf("%d\n", solve(origin, target, status_table));
    }

    return 0;
}
