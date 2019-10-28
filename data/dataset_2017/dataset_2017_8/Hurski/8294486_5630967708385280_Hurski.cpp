
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
    std::int64_t d = 0;
    std::int64_t n = 0;
    std::int64_t start = 0;
    std::int64_t speed = 0;
    long double result = 0;
    long double tmp_result = 0;
    
    std::fscanf(ifile, "%ld %ld", &d, &n);

    for(auto i = 0; i < n; ++i) {
        std::fscanf(ifile, "%ld %ld", &start, &speed);
        tmp_result = static_cast<long double>(d - start);
        tmp_result /= speed;
        //if((0 == result) || (result > tmp_result))
        if(tmp_result > result )
            result = tmp_result;
    }

    result = d / result;
    
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
