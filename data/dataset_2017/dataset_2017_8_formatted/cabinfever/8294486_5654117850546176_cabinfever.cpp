#include <bits/stdc++.h>

using namespace std;

int T, n;
int r, o, y, g, b, v;
int ans = 0;
string s;

vector<int> a[7];
int c[7];
char cc[7];

void dfs(int pre, int n) {
  if (!n)
    return;
  int len = a[pre].size();
  int maxx = 0, maxp = 0;
  for (int i = 0; i < len; i++)
    if (c[a[pre][i]] > maxx) {
      maxx = c[a[pre][i]];
      maxp = a[pre][i];
    }
  s += cc[maxp];
  c[maxp]--;
  dfs(maxp, n - 1);
}

int main() {
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
  cin >> T;
  for (int i = 1; i < 7; i++)
    a[0].push_back(i);
  cc[1] = 'R';
  cc[2] = 'O';
  cc[3] = 'Y';
  cc[4] = 'G';
  cc[5] = 'B';
  cc[6] = 'V';
  a[1].push_back(3);
  a[1].push_back(4);
  a[1].push_back(5);
  a[2].push_back(5);
  a[3].push_back(1);
  a[3].push_back(5);
  a[3].push_back(6);
  a[4].push_back(1);
  a[5].push_back(1);
  a[5].push_back(2);
  a[5].push_back(3);
  a[6].push_back(3);
  for (int ii = 1; ii <= T; ii++) {
    s.clear();
    printf("Case #%d: ", ii);
    cin >> n >> r >> o >> y >> g >> b >> v;
    c[1] = r;
    c[2] = o;
    c[3] = y;
    c[4] = g;
    c[5] = b;
    c[6] = v;
    if (r + o + v > n / 2 || y + g + o > n / 2 || b + v + g > n / 2)
      printf("IMPOSSIBLE\n");
    else {
      dfs(0, n);
      cout << s << endl;
    }
  }
  return 0;
}
