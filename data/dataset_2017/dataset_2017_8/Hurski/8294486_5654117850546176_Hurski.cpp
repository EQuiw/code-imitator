
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <chrono>
#include <cstdint>
#include <vector>
#include <map>
#include <math.h>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <bitset>
#include <queue>
#include <unordered_map>
#include <set>
#include <stack>
#include <fstream>

FILE * ifile = nullptr;
std::ofstream ofile;

#define MAX_COLOR 6
#define RED 1 << 0
#define BLUE 1 << 1
#define YELLOW 1 << 2

struct color_t {
    int mask {0};
    int rank;
    int counter;
    char letter {'.'};
};

int rank[MAX_COLOR];

void add_rank(int mask, int value) {
    if(mask & RED) {
        rank[0] += value;
        rank[1] += value;
        rank[5] += value;
    }

    if(mask & BLUE) {
        rank[3] += value;
        rank[4] += value;
        rank[5] += value;
    }

    if(mask & YELLOW) {
        rank[1] += value;
        rank[2] += value;
        rank[3] += value;
    }
}

void decrease_rank(int mask) {
    if(mask & RED) {
        --rank[0];
        --rank[1];
        --rank[5];
    }

    if(mask & BLUE) {
        --rank[3];
        --rank[4];
        --rank[5];
    }

    if(mask & YELLOW) {
        --rank[1];
        --rank[2];
        --rank[3];
    }
}

void solve(int _case) {

    int     n;
    color_t colors[MAX_COLOR];

    colors[0].mask      = RED; 
    colors[0].rank      = 0;
    colors[0].letter    = 'R'; 
    colors[1].mask      = RED | YELLOW; 
    colors[1].rank      = 1;
    colors[1].letter    = 'O'; 
    colors[2].mask      = YELLOW; 
    colors[2].rank      = 2;
    colors[2].letter    = 'Y'; 
    colors[3].mask      = YELLOW | BLUE; 
    colors[3].rank      = 3;
    colors[3].letter    = 'G'; 
    colors[4].mask      = BLUE; 
    colors[4].rank      = 4;
    colors[4].letter    = 'B'; 
    colors[5].mask      = BLUE | RED; 
    colors[5].rank      = 5;
    colors[5].letter    = 'V'; 

    std::fscanf(ifile, "%d %d %d %d %d %d %d", &n, &colors[0].counter, &colors[1].counter, &colors[2].counter, &colors[3].counter, &colors[4].counter, &colors[5].counter);

    for(auto i = 0; i < MAX_COLOR; ++i)
        rank[i] = 0;

    add_rank(RED, colors[0].counter);
    add_rank(RED | YELLOW, colors[1].counter);
    add_rank(YELLOW, colors[2].counter);
    add_rank(YELLOW | BLUE, colors[3].counter);
    add_rank(BLUE, colors[4].counter);
    add_rank(BLUE | RED, colors[5].counter);

    for(auto i = 0; i < MAX_COLOR; ++i)
        for(auto j = 0; j < MAX_COLOR - 1; ++j)
            if((0 != colors[j + 1].counter) && ((0 == colors[j].counter) || rank[colors[j].rank] < rank[colors[j + 1].rank]))
                std::swap(colors[j], colors[j + 1]);

    int mask = 0;
    int first = 0;
    int last = 0;
    int total = 0;
    std::string result;

    result.reserve(n);
    for(auto k = 0; k < n; ++k) {
        bool found = false;
        for(auto i = 0; i < MAX_COLOR; ++i) {
            if(0 == colors[i].counter) break;
            if(colors[i].mask & mask) continue;
            if(result.empty()) first = colors[i].mask;
            last = colors[i].mask;
            result += colors[i].letter;
            mask = colors[i].mask;
            decrease_rank(colors[i].mask);
            --colors[i].counter;
            bool update = true;
            for(auto f = i; update && (f < MAX_COLOR); ++f) {
                update = false;
                for(auto j = i; j < MAX_COLOR - 1; ++j)
                    if((0 != colors[j + 1].counter) && ((0 == colors[j].counter) || (rank[colors[j].rank] < rank[colors[j + 1].rank]) || ((rank[colors[j].rank] == rank[colors[j + 1].rank]) && (colors[j + 1].mask & first)))) {
                        std::swap(colors[j], colors[j + 1]);
                        update = true;
                    }
            }
            found = true;
            break;
        }
        if(!found) {
            ofile << "Case #" << _case << ": IMPOSSIBLE\n";
            return;
        }
    }

    if((1 != n) && (first & last))
        ofile << "Case #" << _case << ": IMPOSSIBLE\n";
    else
        ofile << "Case #" << _case << ": " << result << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    ifile = fopen("1.in","r");
    ofile.open("output.out");
    ofile << std::setprecision(6) << std::fixed;
    
    int n = 0;
    std::fscanf(ifile, "%d", &n);
    for(auto i = 0; i < n; ++i)
        solve(i + 1);

    ofile.close();

    return 0;
}
