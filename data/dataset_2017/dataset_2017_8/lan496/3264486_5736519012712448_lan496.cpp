#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define ALL(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ld EPS = 1e-8;

int solve(const string& S, int K) {
  int N = S.length();
  vector<int> a(N);
  REP(i,N) {
    if(S[i] == '+') a[i] = 0;
    else a[i] = 1;
  }
  int res = 0;
  REP(i, N - K + 1) {
    if(a[i] % 2) {
      ++res;
      REP(j,K) ++a[i + j];
    }
  }
  for(int i = N - K + 1; i < N; ++i) {
    if(a[i] % 2) return -1;
  }
  return res;
}

int main(){
  int T;
  cin >> T;
  REP(t, T) {
    string S;
    int K;
    cin >> S >> K;
    int res = solve(S, K);
    cout << "Case #" << t + 1 << ": " << (res == -1 ? "IMPOSSIBLE" : to_string(res)) << endl;
  }
  return 0;
}

