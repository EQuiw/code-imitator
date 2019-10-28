#include <bits/stdc++.h>
using namespace std;

int N;
int R, O, Y, G, B, V;
char color[7] = "ROYGBV";
int num[7];

int choose(char ch)
{
  int mx = 0;
  int ret = 0;
  for (int i = 0; i < 6; ++i) {
    if (color[i] != ch && num[i] > mx) {
      mx = num[i];
      ret = i;
    }
  }
  return ret;
}

void solve()
{
  cin >> N >> R >> O >> Y >> G >> B >> V;
  num[0] = R;
  num[1] = O;
  num[2] = Y;
  num[3] = G;
  num[4] = B;
  num[5] = V;

  int cnt = 0;
  int c1 = 0, c2 = 0;
  if (R) {
    ++cnt;
  }
  if (B) {
    ++cnt;
  }
  if (Y) {
    ++cnt;
  }
  if (1 == cnt || 2*R>N || 2*B>N || 2*Y>N) {
    puts("IMPOSSIBLE");
    return ;
  }
  string ans = "";
  for (int i = 0; i < N; ++i) {
    int mx = 0;
    if (i == 0) {
      mx = choose('#');
    } else {
      mx = choose(ans[i-1]);
    }
    ans += color[mx];
    num[mx]--;
  }
  if (ans[0] == ans[N-1]) {
    swap(ans[N-1], ans[N-2]);
    if (ans[N-2] == ans[N-3]) {
      cout << "fucked" << endl;
    }
  }
  puts(ans.c_str());
}

int main()
{
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    printf("Case #%d: ", cas);
    solve();
  }
}
