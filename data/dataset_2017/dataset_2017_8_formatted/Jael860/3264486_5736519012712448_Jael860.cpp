#include <bits/stdc++.h>

#define debug(x) cerr << #x << ": " << x << endl;
#define print(x) cerr << x << endl;

#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define REP(i, x, y) for (int i = x; i < y; i++)
#define REPIT(it, A)                                                           \
  for (typeof(A.begin()) it = (A.begin()); it != A.end(); it++)
#define fst first
#define snd second
#define sqr(x) ((x) * (x))

#define fastio                                                                 \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);
#define ones(x) __builtin_popcountll(x)
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;

vi v;

void clean(int ini, int j) { REP(i, ini, j) v[i] = 1 - v[i]; }

int main() {
  fastio;

  int T;
  cin >> T;
  REP(test, 1, T + 1) {
    cout << "Case #" << test << ": ";
    string s;
    int k;
    cin >> s >> k;
    v.clear();
    REP(i, 0, s.size()) v.pb(s[i] == '+');
    int res = 0;
    bool flg = false;

    int i = 0;
    int j = v.size() - 1;
    while (i <= j && !flg) {
      //			cerr<<i << " "<<j<<endl;
      //			cerr<<i+k<<" "<<j+1<<endl;
      //			cerr<<j-k+1<<" "<<i<<endl;
      //			cerr<<"-----"<<endl;
      if (!v[i]) {
        if (i + k > j + 1)
          flg = true;
        else {
          clean(i, i + k);
          i++;
          res++;
        }
      } else if (!v[j]) {
        int ini = j - k + 1;
        if (ini < i)
          flg = true;
        else {
          clean(ini, ini + k);
          res++;
          j--;
        }
      } else {
        i++;
        j--;
      }
    }
    REP(i, 0, v.size()) if (!v[i]) flg = true;
    if (flg)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << res << endl;
  }

  return 0;
}
