#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define PII pair<int, int>
#define maxn (1e5 + 7)

string let = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
void mf() {
  // freopen("input.in","r",stdin);

  freopen("Asmall4.in", "r", stdin);
  freopen("Asmall4.ou", "w", stdout);

  // freopen("Alarge.in","r",stdin);
  // freopen("Alarge.ou","w",stdout);
}
int n, m;
int a[50][50];
int xmin[50], ymin[50], xmax[59], ymax[59];
bool check(int x0, int x1, int y0, int y1, int v) {
  for (int i = x0; i <= x1; i++)
    for (int j = y0; j <= y1; j++) {
      if (a[i][j] == v || a[i][j] == 0)
        continue;
      return false;
    }
  return true;
}
void drawFull(int x0, int x1, int y0, int y1, int v) {
  for (int i = x0; i <= x1; i++)
    for (int j = y0; j <= y1; j++) {
      a[i][j] = v;
    }
}
void draw(int x, int y) {
  for (int v = 1; v <= 26; v++)
    if (xmin[v] != 40) {
      int xmi = min(x, xmin[v]), xma = max(x, xmax[v]), ymi = min(y, ymin[v]),
          yma = max(y, ymax[v]);

      if (check(xmi, xma, ymi, yma, v)) {
        xmin[v] = min(xmin[v], x);
        xmax[v] = max(xmax[v], x);
        ymin[v] = min(ymin[v], y);
        ymax[v] = max(ymax[v], y);
        drawFull(xmi, xma, ymi, yma, v);
        return;
      }
    }
}

void solve() {
  cin >> n >> m;
  cin.ignore(1);
  for (int i = 1; i <= n; i++) {
    string s;
    getline(cin, s);
    for (int j = 1; j <= m; j++) {
      a[i][j] = (s[j - 1] == '?' ? 0 : (s[j - 1] - 'A') + 1);
    }
  }
  for (int i = 1; i <= 26; i++) {
    xmin[i] = ymin[i] = 40;
    xmax[i] = ymax[i] = 0;
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (a[i][j] > 0) {
        int v = a[i][j];
        xmin[v] = min(xmin[v], i);
        xmax[v] = max(xmax[v], i);
        ymin[v] = min(ymin[v], j);
        ymax[v] = max(ymax[v], j);
      }
    }
  for (int v = 1; v <= 26; v++) {
    for (int i = xmin[v]; i <= xmax[v]; i++)
      for (int j = ymin[v]; j <= ymax[v]; j++)
        a[i][j] = v;
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == 0) {
        draw(i, j);
      }
    }
  cout << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int xx = a[i][j] - 1;
      string s = "";
      s += let[xx];
      cout << s.c_str();
    }
    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
#ifdef tuanh
  mf();
#endif
  int ntest;
  cin >> ntest;
  // cout<<let.length()<<endl;
  for (int nt = 1; nt <= ntest; nt++) {
    cout << "Case #" << nt << ": ";
    solve();
  }
  return 0;
}