#include <bits/stdc++.h>

using namespace std;
#define Fill(a, b) memset(a, b, sizeof(a))
#define Debug(x) cout << #x << "=" << (x) << endl;
#define fop(i, a, b) for (i = a; i < b; i++)
#define fope(i, a, b) for (i = a; i <= b; i++)
#define fom(i, a, b) for (i = a; i > b; i--)
#define fome(i, a, b) for (i = a; i >= b; i--)
typedef unsigned long long LL;
typedef pair<int, int> P;
const LL inf = 1LL << 61;
const LL mod = 1000000007;
const int maxn = 64;

LL pow2_arr[maxn];
int main() {
  std::ios::sync_with_stdio(false);
  streambuf *backup;
  ifstream fin;
  fin.open("C-small-1-attempt0.in");
  backup = cin.rdbuf(); // back up cin's streambuf
  cin.rdbuf(fin.rdbuf());
  ofstream out("out.txt");
  int i = 0, j = 0, kase = 0;
  pow2_arr[0] = 1;
  for (i = 1; i < maxn; i++) {
    pow2_arr[i] = pow2_arr[i - 1] * 2;
  }
  // Debug(pow2_arr[maxn-1]);
  int t;
  LL n, k;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    int lv = 0;
    for (lv = 0; lv < maxn - 1; lv++) {
      if (pow2_arr[lv] <= k && pow2_arr[lv + 1] > k) {
        break;
      }
    }
    LL suml = pow2_arr[lv] - 1;
    LL lev_sum = min(pow2_arr[lv], n - suml);
    if ((n - suml) % lev_sum == 0) {
      LL len = (n - suml) / lev_sum;
      if (len % 2LL == 0)
        out << "Case #" << ++kase << ": " << len / 2 << " " << len / 2 - 1
            << endl;
      else
        out << "Case #" << ++kase << ": " << len / 2 << " " << len / 2 << endl;
    } else {
      LL sml_num = (n - suml) / lev_sum, big_num = (n - suml) / lev_sum + 1;
      LL big_sum = n - suml - sml_num * lev_sum;
      // Debug(big_sum);
      if (k - suml <= big_sum) {
        if (big_num % 2 == 0)
          out << "Case #" << ++kase << ": " << big_num / 2 << " "
              << big_num / 2 - 1 << endl;
        else
          out << "Case #" << ++kase << ": " << big_num / 2 << " " << big_num / 2
              << endl;
      } else {
        if (sml_num % 2 == 0)
          out << "Case #" << ++kase << ": " << sml_num / 2 << " "
              << sml_num / 2 - 1 << endl;
        else
          out << "Case #" << ++kase << ": " << sml_num / 2 << " " << sml_num / 2
              << endl;
      }
    }
  }

  return 0;
}
/*
3
20 4
20 5
33 9
2 2
2 1
2 1
*/
