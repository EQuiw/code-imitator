
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

bool solve(string s, int k, int &ans) {
  ans = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '-') {
      if (i + k - 1 >= s.length())
        return false;
      for (int j = 0; j < k; j++) {
        if (s[i + j] == '-')
          s[i + j] = '+';
        else
          s[i + j] = '-';
      }
      ans++;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int NUMBER_OF_TESTS;
  cin >> NUMBER_OF_TESTS;
  for (int t = 1; t <= NUMBER_OF_TESTS; t++) {
    string s;
    int k, ans;
    cin >> s >> k;
    cout << "Case #" << t << ": ";
    if (solve(s, k, ans))
      cout << ans << "\n";
    else
      cout << "IMPOSSIBLE"
           << "\n";
  }
  return 0;
}
