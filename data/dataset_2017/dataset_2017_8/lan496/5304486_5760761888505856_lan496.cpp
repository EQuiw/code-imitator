#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define ALL(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;

const int INF = 1e9;
const ld EPS = 1e-8;

vector<string> solve(const vector<string>& cake) {
  int R = cake.size();
  int C = cake[0].length();
  vector<string> res = cake;

  REP(i,R) {
    int pos = -1;
    REP(j,C) if(res[i][j] != '?') {
      pos = j;
      break;
    }
    if(pos == -1) continue;
    REP(j,C) {
      if(res[i][j] == '?') {
        res[i][j] = res[i][pos];
      }else{
        pos = j;
      }
    }
  }

  int tmp = 0;
  while(res[tmp][0] == '?') ++tmp;
  REP(i,tmp) res[i] = res[tmp];

  REP(i,R - 1) if(res[i + 1][0] == '?') res[i + 1] = res[i];

  return res;
}

int main(){
  int T;
  cin >> T;
  REP(t,T) {
    int R, C;
    cin >> R >> C;
    vector<string> cake(R);
    REP(i,R) cin >> cake[i];

    vector<string> res = solve(cake);
    cout << "Case #" << t + 1 << ":" << endl;
    REP(i,R) cout << res[i] << endl;
  }
  return 0;
}

