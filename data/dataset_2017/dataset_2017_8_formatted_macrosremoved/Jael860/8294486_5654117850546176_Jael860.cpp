#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;

const int MAXN = 1200;
const string OUT = "IMPOSSIBLE";
int N, R, O, Y, G, B, V;
pair<int, char> arr[10];
bool check(string res) {

  for (int i = 0; i < res.size() - 1; i++) {
    if (res[i] == res[i + 1])
      return false;
  }
  return true;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ;
  int T;

  cin >> T;

  for (int test = 1; test < T + 1; test++) {
    cout << "Case #" << test << ": ";
    cin >> N >> R >> O >> Y >> G >> B >> V;
    if (V > 0 && V >= Y) {
      cout << OUT << endl;
      continue;
    }
    if (G > 0 && G >= R) {
      cout << OUT << endl;
      continue;
    }
    if (O > 0 && O >= B) {
      cout << OUT << endl;
      continue;
    }
    /*
        arr[0] = mp(Y - V, V);
        arr[1] = mp(R - G, G);
        arr[2] = mp(B - O, O);*/;
    arr[0] = make_pair(Y, 'Y');
    arr[1] = make_pair(R, 'R');
    arr[2] = make_pair(B, 'B');
    string res = "";
    int ls = -1;
    bool flg = true;
    int ini = -1;
    for (int i = 0; i < N; i++) {
      int mx = 0;
      int id = -1;
      for (int j = 0; j < 3; j++) {
        if (j == ls)
          continue;
        if (arr[j].first > mx) {
          mx = arr[j].first;
          id = j;
        } else if (arr[j].first == mx && mx > 0 && j == ini) {
          id = j;
        }
      }
      if (i == 0)
        ini = id;
      // cerr<<arr[0].fst<<" "<<arr[1].fst<<" "<<arr[2].fst<<endl;
      if (id == -1) {
        flg = false;
        break;
      }
      ls = id;
      arr[id].first--;
      res += arr[id].second;
    }
    if (!flg || res[0] == res[N - 1]) {
      cout << OUT << endl;
      continue;
    }
    cout << res << endl;
  }

  return 0;
}
