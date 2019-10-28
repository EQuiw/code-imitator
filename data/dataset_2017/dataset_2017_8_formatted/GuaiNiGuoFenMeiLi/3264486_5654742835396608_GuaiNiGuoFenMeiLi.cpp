#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <utility>
#include <vector>

using namespace std;

void solve(long long N, set<long long> &Set) {
  if (N == 0) {
    return;
  }
  long long L = (N - 1) / 2;
  long long R = N - 1 - L;
  if (!Set.count(N)) {
    Set.insert(N);
    solve(L, Set);
    solve(R, Set);
  }
}

int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-small-1-attempt0.out", "w", stdout);

  int T;
  cin >> T;
  for (int test = 1; test <= T; ++test) {
    long long N, K;
    cin >> N >> K;
    set<long long> Set;
    solve(N, Set);
    vector<long long> V;
    for (set<long long>::iterator i = Set.begin(); i != Set.end(); ++i) {
      V.push_back(*i);
    }
    map<long long, long long> C;
    C[N] = 1;
    for (int i = V.size() - 2; i >= 0; --i) {
      C[V[i]] = 0;
      if (C.count(V[i] * 2)) {
        C[V[i]] += C[V[i] * 2];
      }
      if (C.count(V[i] * 2 + 1)) {
        C[V[i]] += C[V[i] * 2 + 1] * 2;
      }
      if (C.count(V[i] * 2 + 2)) {
        C[V[i]] += C[V[i] * 2 + 2];
      }
      // cout << V[i] << ":" << C[V[i]] << endl;
    }
    long long r = 0;
    for (int i = V.size() - 1; i >= 0; --i) {
      r += C[V[i]];
      if (r >= K) {
        long long L = (V[i] - 1) / 2;
        long long R = V[i] - 1 - L;
        cout << "Case #" << test << ": " << R << " " << L << endl;
        break;
      }
    }
  }

  return 0;
}
