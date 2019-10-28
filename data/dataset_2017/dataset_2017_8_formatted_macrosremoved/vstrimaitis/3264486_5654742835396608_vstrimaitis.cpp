
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

ull hob(ull n) {
  if (!n)
    return 0;
  ull ret = 1;
  while (n >>= 1)
    ret <<= 1;
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int NUMBER_OF_TESTS;
  cin >> NUMBER_OF_TESTS;
  for (int t = 1; t <= NUMBER_OF_TESTS; t++) {
    ull n, k;
    cin >> n >> k;
    ull h = hob(k);
    ull lo = k & (~h);
    h <<= 1;
    ull left = (n - lo) / h, right = (n - (lo + h / 2)) / h;
    cout << "Case #" << t << ": " << left << " " << right << "\n";
  }
  return 0;
}
