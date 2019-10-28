#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;

vi v;

void clean(int ini, int j) {
  for (int i = ini; i < j; i++)
    v[i] = 1 - v[i];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ;

  int T;
  cin >> T;
  for (int test = 1; test < T + 1; test++) {
    cout << "Case #" << test << ": ";
    string s;
    int k;
    cin >> s >> k;
    v.clear();
    for (int i = 0; i < s.size(); i++)
      v.push_back(s[i] == '+');
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
    for (int i = 0; i < v.size(); i++)
      if (!v[i])
        flg = true;
    if (flg)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << res << endl;
  }

  return 0;
}
