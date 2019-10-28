#include <cassert>
#include <iostream>
#include <map>
#include <utility>
using namespace std;

int T;
long long K, N;
typedef map<pair<long long, long long>, long long> tree;
tree spaces;
map<pair<long long, long long>, tree> memo;
map<pair<long long, long long>, long long> bsearch(long long x, long long y) {
  if (!memo.count({x, y})) {
    tree structure;
    assert((x - y == 0) || (x - y == 1));
    structure[{x, y}]++;
    if (!(x == 0 && y == 0)) {
      if (x == 1 && y == 0) {
        structure[{0, 0}]++;
      } else if (x % 2 == 1) {
        if (x == y) {
          auto left = bsearch(x / 2, y / 2);
          auto right = bsearch(x / 2, y / 2);
          for (auto x : left) {
            structure[x.first] += x.second;
          }
          for (auto x : right) {
            structure[x.first] += x.second;
          }
        } else {
          auto left = bsearch(x / 2, y / 2);
          auto right = bsearch(x / 2, y / 2 - 1);
          for (auto x : left) {
            structure[x.first] += x.second;
          }
          for (auto x : right) {
            structure[x.first] += x.second;
          }
        }
      } else {
        if (x == y) {
          auto left = bsearch(x / 2, y / 2 - 1);
          auto right = bsearch(x / 2, y / 2 - 1);
          for (auto x : left) {
            structure[x.first] += x.second;
          }
          for (auto x : right) {
            structure[x.first] += x.second;
          }
        } else {
          auto left = bsearch(x / 2, y / 2);
          auto right = bsearch(x / 2 - 1, y / 2);
          for (auto x : left) {
            structure[x.first] += x.second;
          }
          for (auto x : right) {
            structure[x.first] += x.second;
          }
        }
      }
    }
    memo[{x, y}] = structure;
  }
  return memo[{x, y}];
}

int main() {
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> N >> K;
    spaces.clear();
    if (N % 2 == 1) {
      spaces = bsearch(N / 2, N / 2);
    } else {
      spaces = bsearch(N / 2, N / 2 - 1);
    }
    cout << "Case #" << t << ": ";
    long long total = 0;
    for (auto x = spaces.rbegin(); x != spaces.rend(); x++) {
      total += x->second;
      if (total >= K) {
        cout << x->first.first << " " << x->first.second << endl;
        break;
      }
    }
  }
  return 0;
}