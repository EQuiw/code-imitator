#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define ALL(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ld EPS = 1e-8;

ld solve(int D, const vector<int>& K, const vector<int>& S) {
  int N = K.size();
  vector<ld> t(N);
  REP(i,N) t[i] = (ld)(D - K[i]) / S[i];
  sort(t.rbegin(), t.rend());
  ld res = D / t[0];
  return res;
}

int main(){
  int T;
  cin >> T;
  REP(t,T) {
    int D, N;
    cin >> D >> N;
    vector<int> K(N), S(N);
    REP(i,N) cin >> K[i] >> S[i];
    ld res = solve(D, K, S);
    cout << "Case #" << fixed << setprecision(10) << t + 1 << ": " << res << endl;
  }
  return 0;
}

