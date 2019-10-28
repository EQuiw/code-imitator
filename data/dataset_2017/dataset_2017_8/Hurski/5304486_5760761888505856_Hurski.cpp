
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

#define MAX_N 1001

void solve(int _case) {
    std::int64_t row = 0;
    std::int64_t col = 0;
    char buf[30];
    std::unordered_map<char, int> minX;
    std::unordered_map<char, int> minY;
    std::unordered_map<char, int> maxX;
    std::unordered_map<char, int> maxY;
    
    std::fscanf(ifile, "%ld %ld", &row, &col);

    std::vector <std::vector<char>> cake;

    cake.resize(row);
    for(auto y = 0; y < row; y++){
        std::fscanf(ifile, "%29s", &buf);
        cake[y].resize(col);
        for(auto x = 0; x < col; x++) {
            auto ch = buf[x];
            cake[y][x] = ch;
            if(ch != '?') {
                if(minX.end() != minX.find(ch)) {
                    minX[ch] = std::min(x, minX[ch]);
                    minY[ch] = std::min(y, minY[ch]);
                    maxX[ch] = std::max(x, maxX[ch]);
                    maxY[ch] = std::max(y, maxY[ch]);
                } else {
                    minX[ch] = x;
                    minY[ch] = y;
                    maxX[ch] = x;
                    maxY[ch] = y;
                }
            }
        }
    }

    for(auto iter : minX) {
        auto ch = iter.first;

        bool exit = false;
        for(auto x = minX[ch] - 1; !exit && x >= 0; --x) {
            for(auto y = minY[ch]; !exit && y <= maxY[ch]; ++y)
                exit = cake[y][x] != '?';
            if(!exit) --minX[ch];
        }

        exit = false;
        for(auto x = maxX[ch] + 1; !exit && x < col; ++x) {
            for(auto y = minY[ch]; !exit && y <= maxY[ch]; ++y)
                exit = cake[y][x] != '?';
            if(!exit) ++maxX[ch];
        }

        exit = false;
        for(auto y = minY[ch] - 1; !exit && y >= 0; --y) {
            for(auto x = minX[ch]; !exit && x <= maxX[ch]; ++x)
                exit = cake[y][x] != '?';
            if(!exit) --minY[ch];
        }

        exit = false;
        for(auto y = maxY[ch] + 1; !exit && y < row; ++y) {
            for(auto x = minX[ch]; !exit && x <= maxX[ch]; ++x)
                exit = cake[y][x] != '?';
            if(!exit) ++maxY[ch];
        }

        for(auto x = minX[ch]; x <= maxX[ch]; ++x)
            for(auto y = minY[ch]; y <= maxY[ch]; ++y)
                cake[y][x] = ch;
    }

    ofile << "Case #" << _case << ":\n";
    for(auto y = 0; y < row; ++y) {
        for(auto x = 0; x < col; ++x)
            ofile << cake[y][x];
        ofile << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    ifile = fopen("1.in","r");
    ofile.open("output.out");
    
    int n = 0;
    std::fscanf(ifile, "%d", &n);
    for(auto i = 0; i < n; ++i)
        solve(i + 1);

    ofile.close();

    return 0;
}
