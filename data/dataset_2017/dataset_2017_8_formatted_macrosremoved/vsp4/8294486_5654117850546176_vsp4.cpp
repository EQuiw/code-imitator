#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef long long int slong;
typedef pair<int, int> pii;
typedef pair<slong, slong> pll;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    pbds;
typedef set<int>::iterator sit;
typedef map<int, int>::iterator mit;
typedef vector<int>::iterator vit;

const int MOD = 1000000007;
const int MAXN = 100;
const int SQRTN = 550;
const int LOGN = 60;
const int INT_INFINITY = 1001001001;
const int LIMIT = 1e6;

const slong LONG_INFINITY = 1001001001001001001ll;
const slong LONG_LIMIT = 200100100100101ll;

const double DOUBLE_INFINITY = 1e16;

int N, R, O, Y, G, B, V;

int main() {

  cout.tie(0);
  cin.tie(0);

  int t, T, i, j;

  cin >> T;

  for (t = 1; t <= T; t++) {
    cin >> N >> R >> O >> Y >> G >> B >> V;

    vector<pair<int, char>> data;

    data.push_back(make_pair(R, 'R'));
    data.push_back(make_pair(Y, 'Y'));
    data.push_back(make_pair(B, 'B'));

    sort((data).begin(), (data).end(), greater<pair<int, char>>());

    cout << "Case #" << t << ": ";

    if (data[0].first == 1) {
      for (i = 0; i < 3; i++) {
        if (data[i].first) {
          cout << data[i].second;
        }
      }
    } else {
      if (data[0].first <= (data[1].first + data[2].first)) {
        vector<pair<int, char>> back = data;

        int extra = (data[1].first + data[2].first) - data[0].first;

        int a, b, c;
        a = b = c = 0;

        for (i = 0; i < extra; i++) {
          a++;
          b++;
          c++;
          cout << data[0].second << data[1].second << data[2].second;
        }

        data[1].first -= extra;
        data[2].first -= extra;

        for (i = 0; i < data[1].first; i++) {
          a++;
          b++;
          cout << data[0].second << data[1].second;
        }

        for (i = 0; i < data[2].first; i++) {
          a++;
          c++;
          cout << data[0].second << data[2].second;
        }

        assert(a == back[0].first);
        assert(b == back[1].first);
        assert(c == back[2].first);
      } else {
        cout << "IMPOSSIBLE";
      }
    }

    cout << endl;
  }

  return 0;
}
