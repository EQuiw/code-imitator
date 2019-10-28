
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
    char str[MAX_N];
    int data[MAX_N];
    int adj[MAX_N];
    int n = 0;
    int k = 0;
    int counter = 0;
    int sum = 0;

    std::fscanf(ifile, "%1000s %d", str, &k);

    for(n = 0; n < MAX_N; ++n){
        if(0 == str[n]) break;
        data[n] = '-' == str[n] ? 0 : 1;
        adj[n] = 0;
    }

    for(auto i = 0; i < n; ++i) {
        sum += adj[i];
        data[i] = (sum + data[i]) & 1;
        if(0 == data[i] && i < (n - k + 1)) {
            ++counter;
            ++sum;
            data[i] = 1;
            --adj[i + k];
        }
    }
    
    for(auto i = 0; i < n; ++i)
        if(0 == data[i]) {
            ofile << "Case #" << _case << ": IMPOSSIBLE\n";
            return;
        }

    ofile << "Case #" << _case << ": " << counter << "\n";
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
