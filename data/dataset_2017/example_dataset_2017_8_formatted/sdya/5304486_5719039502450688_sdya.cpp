#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#pragma comment(linker, "/STACK:256000000")

using namespace std;

void readData() {}

struct State {
  long long hd, ad;
  long long hk, ak;
  State(long long hd, long long ad, long long hk, long long ak)
      : hd(hd), ad(ad), hk(hk), ak(ak) {}
  bool operator<(const State &other) const {
    return make_pair(make_pair(hd, ad), make_pair(hk, ak)) <
           make_pair(make_pair(other.hd, other.ad),
                     make_pair(other.hk, other.ak));
  }
};

long long hd, ad, hk, ak, b, d;

void update(State t, map<State, int> &M, int value, queue<State> &q) {
  if (M.count(t) == 0) {
    M[t] = value;
    q.push(t);
  }
}

void solve(int test) {
  cin >> hd >> ad >> hk >> ak >> b >> d;
  map<State, int> M;

  M[State(hd, ad, hk, ak)] = 0;
  queue<State> q;
  q.push(State(hd, ad, hk, ak));

  int res = -1;
  while (!q.empty()) {
    State current = q.front();
    int w = M[current];
    q.pop();
    if (current.hk <= 0) {
      res = M[current];
      break;
    }
    if (current.hd <= 0) {
      continue;
    }

    update(State(current.hd - current.ak, current.ad, current.hk - current.ad,
                 current.ak),
           M, w + 1, q);
    update(
        State(current.hd - current.ak, current.ad + b, current.hk, current.ak),
        M, w + 1, q);
    update(State(hd - current.ak, current.ad, current.hk, current.ak), M, w + 1,
           q);

    long long value = max(0LL, current.ak - d);
    update(State(current.hd - value, current.ad, current.hk, value), M, w + 1,
           q);
  }

  if (res == -1) {
    printf("Case #%d: IMPOSSIBLE\n", test);
  } else {
    printf("Case #%d: %d\n", test, res);
  }
}

int main(int argc, char *argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int left_bound, right_bound;

  /*freopen(argv[3], "w", stdout);
  sscanf(argv[1], "%d", &left_bound);
  sscanf(argv[2], "%d", &right_bound);*/

  int t;
  cin >> t;
  left_bound = 1, right_bound = t;
  for (int i = 1; i <= t; ++i) {
    if (i >= left_bound && i <= right_bound) {
      solve(i);
    } else {
      readData();
    }
    cerr << i << ": " << clock() << endl;
  }

  return 0;
}
