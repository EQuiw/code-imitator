
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <climits>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::pair<int, int> pii;
template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T>
using max_heap = std::priority_queue<T, std::vector<T>, std::less<T>>;
using namespace std;

string grid[25];
int rowCnt[25], colCnt[25];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int NUMBER_OF_TESTS;
  cin >> NUMBER_OF_TESTS;
  for (int t = 1; t <= NUMBER_OF_TESTS; t++) {
    int r, c;
    cin >> r >> c;
    for (int i = (0); i < (r); i++) {
      cin >> grid[i];
    }
    for (int i = (0); i < (r); i++) {
      for (int j = (0); j < (c); j++) {
        if (grid[i][j] != '?') {
          rowCnt[i]++;
          colCnt[j]++;
        }
      }
    }

    for (int i = (0); i < (r); i++) {
      char curr = '?';
      for (int j = (0); j < (c); j++) {
        if (grid[i][j] != '?') {
          curr = grid[i][j];
          for (int jj = (j - 1); jj >= (0); jj--) {
            if (grid[i][jj] != '?')
              break;
            grid[i][jj] = curr;
          }
        }
        if (curr != '?')
          grid[i][j] = curr;
      }
    }

    for (int i = (1); i < (r); i++) {
      if (grid[i][0] == '?') {
        grid[i] = grid[i - 1];
      }
    }
    for (int i = (r - 2); i >= (0); i--) {
      if (grid[i][0] == '?')
        grid[i] = grid[i + 1];
    }

    cout << "Case #" << t << ":"
         << "\n";
    for (int i = (0); i < (r); i++)
      cout << grid[i] << "\n";
  }
  return 0;
}
