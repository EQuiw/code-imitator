#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pp;

const int INF = 1e9;
const ld EPS = 1e-8;

struct Compare {
  bool operator()(const pp &lhs, const pp &rhs) {
    if (lhs.first != rhs.first)
      return lhs.first < rhs.first;
    return lhs.second > rhs.second;
  }
};

pair<int, int> solve(int N, int K) {
  priority_queue<pp, vector<pp>, Compare> que;
  que.push(make_pair(N, 0));
  pair<int, int> res;

  for (int i = 0; i < (int)(K); i++) {
    auto p = que.top();
    que.pop();
    // cout << p.first << " " << p.second << endl;
    int tmp = (p.first - 1) / 2;
    if (i == K - 1) {
      res = make_pair(p.first - 1 - tmp, tmp);
    } else {
      if (tmp) {
        que.push(make_pair(tmp, p.second));
      }
      if (p.first - 1 - tmp) {
        que.push(make_pair(p.first - 1 - tmp, p.second + tmp + 1));
      }
    }
  }

  return res;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < (int)(T); t++) {
    int N, K;
    cin >> N >> K;
    pair<int, int> res = solve(N, K);
    cout << "Case #" << t + 1 << ": " << res.first << " " << res.second << endl;
  }
  return 0;
}
