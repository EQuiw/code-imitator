#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

long long dx[4] = {1, 0, -1, 0};
long long dy[4] = {0, -1, 0, 1};

long long nextInt() {
  long long a;
  cin >> a;
  return a;
}
char nextChar() {
  char a;
  cin >> a;
  return a;
}
double nextDouble() {
  double a;
  cin >> a;
  return a;
}
string nextString() {
  string a;
  cin >> a;
  return a;
}

template <class T> void inputVector(vector<T> &v, long long n) {
  v.resize(n);
  for (long long i = 0; i < v.size(); i++)
    cin >> v[i];
}

class Info {
public:
  long long node;
  long long leftDist;
  long long speed;
  double time;

  Info() {}
  Info(long long node, long long leftDist, long long speed, double time) {
    this->node = node;
    this->leftDist = leftDist;
    this->speed = speed;
    this->time = time;
  }

  bool operator<(const Info &a) const { return time > a.time; }
};

signed main() {
  long long T;
  cin >> T;

  for (long long loop = (1); loop <= (T); loop++) {
    long long N, Q;
    cin >> N >> Q;

    vector<long long> E(N), S(N);
    for (long long i = 0; i < (N); i++)
      cin >> E[i] >> S[i];

    long long D[110][110];
    for (long long i = 0; i < (N); i++)
      for (long long j = 0; j < (N); j++)
        cin >> D[i][j];

    for (long long i = 0; i < (Q); i++) {
      long long gomi;
      cin >> gomi;
      cin >> gomi;
    }

    vector<double> time(N, LLONG_MAX);
    time[0] = 0;

    priority_queue<Info> q;
    q.push(Info(0, 0, 1, 0));
    while (!q.empty()) {
      auto nowinfo = q.top();
      q.pop();

      if (nowinfo.node == N - 1) {
        printf("Case #%d: %.8f\n", loop, nowinfo.time);
        break;
      }

      for (long long i = (nowinfo.node + 1); i <= (N - 1); i++) {
        long long dist = D[nowinfo.node][i];
        if (dist == -1)
          continue;
        if (dist <= nowinfo.leftDist) {
          q.push(Info(i, nowinfo.leftDist - dist, nowinfo.speed,
                      nowinfo.time + (double)dist / nowinfo.speed));
        }
        if (dist <= E[nowinfo.node]) {
          q.push(Info(i, E[nowinfo.node] - dist, S[nowinfo.node],
                      nowinfo.time + (double)dist / S[nowinfo.node]));
        }
      }
    }
  }

  return 0;
}
