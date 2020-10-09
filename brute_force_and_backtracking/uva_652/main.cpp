/**
 * UVA - PROBLEM 652 (https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=593)
 * Solution using the A* search algorithm.
 * @author Gabriel Nogueira (Talendar)
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <queue>

using namespace std;
const int NUM_TILES = 3;


class Puzzle {
    public:
    
    char board[NUM_TILES][NUM_TILES];    // tiles
    int x_row, x_col;                    // pos of the x tile
    int depth = 0;                       // distance to the origin state
    string path;                         // path (moves) from the origin to the current state
    string key = "";
    int dist2target;
    Puzzle() {}

    /**
     * Creates a new puzzle configuration by moving the "x" tile in the parent.
     */
    Puzzle(Puzzle parent, char move) {
        this->depth = parent.depth + 1;
        this->path = parent.path + move;

        this->x_row = parent.x_row;
        this->x_col = parent.x_col;

        switch(move) {
            case 'l':  this->x_col--; break;
            case 'u':  this->x_row--; break;
            case 'r':  this->x_col++; break;
            case 'd':  this->x_row++; break;
        }

        memcpy(this->board, parent.board, sizeof(parent.board));
        this->board[parent.x_row][parent.x_col] = this->board[this->x_row][this->x_col];
        this->board[this->x_row][this->x_col] = 'x';

        for(int i = 0; i < NUM_TILES; i++) {
            for(int j = 0; j < NUM_TILES; j++) {
                key += this->board[i][j];
            }
        }

        this->calc_dist();
    }

    vector<char> valid_moves() {
        vector<char> m;

        if(this->x_col < (NUM_TILES - 1))
            m.push_back('r');  
        if(this->x_col > 0)
            m.push_back('l');  
        if(this->x_row > 0)
            m.push_back('u');  
        if(this->x_row < (NUM_TILES - 1))
            m.push_back('d');  

        return m;
    }

    void print() {
        for(int i = 0; i < NUM_TILES; i++) {
            for(int j = 0; j < NUM_TILES; j++) {
                cout << this->board[i][j] << " ";
            }
            cout << endl;
        }
    }

    /**
     * Returns the distance between the current state and the target state.
     */
    void calc_dist() {
        this->dist2target = 0;
        for(int i = 0; i < NUM_TILES; i++) {
            for(int j = 0; j < NUM_TILES; j++) {
                int t_row, t_col;
                if(this->board[i][j] == 'x') {
                    t_row = t_col = NUM_TILES - 1;
                }
                else {
                    int c = this->board[i][j] - '0' - 1;
                    t_row = c/NUM_TILES;
                    t_col = c % NUM_TILES;
                }
                
                this->dist2target += abs(i - t_row) + abs(j - t_col);
            }
        }
    }
};


/**
 * Used by the priority queue to compare two boards. Acts as the evaluation
 * function (f = h + g) for the A* algorithm. 
 */
class BoardComparator {
    public:
    bool operator() (Puzzle p1, Puzzle p2) {
        int f1 = p1.depth + p1.dist2target;
        int f2 = p2.depth + p2.dist2target;
        return f1 > f2;
    }
};


string solve(Puzzle origin)
{
    unordered_map<string, void*> visited;
    priority_queue<Puzzle, vector<Puzzle>, BoardComparator> pq;
    pq.push(origin);

    while(!pq.empty()) {
        Puzzle current = pq.top();  pq.pop();
        visited[current.key];

        if(current.dist2target == 0)
            return current.path;

        vector<char> moves = current.valid_moves();
        for(int i = 0; i < (int) moves.size(); i++) {
            Puzzle p(current, moves[i]);
            if(visited.count(p.key) == 0)
                pq.push(p);
        }
    }

    return "unsolvable";
}


int main()
{
    int n;  cin >> n;
    for(int ex = 0; ex < n; ex++) {
        cin.ignore();

        Puzzle origin;
        for(int i = 0; i < (NUM_TILES * NUM_TILES); i++) {
            char c;  cin >> c;
            int row = i/NUM_TILES, col = i % NUM_TILES;

            origin.key += c;
            origin.board[row][col] = c;
            if(c == 'x') {
                origin.x_row = row;
                origin.x_col = col;
            }
        }

        cout << solve(origin) << endl;
        if(ex != (n-1))
            cout << endl;
    }

    return 0;
}