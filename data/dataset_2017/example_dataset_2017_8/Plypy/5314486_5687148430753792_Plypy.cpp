#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int N, C, M;
vector<int> cust[MAXN];
int cnt[MAXN];
int sum[MAXN];
void solve()
{
  memset(sum, 0, sizeof(sum));
  memset(cnt, 0, sizeof(cnt));
  cin >> N >> C >> M;
  int ans1 = 0, ans2 = 0;
  int mr = 0;
  for (int i = 0; i <= C; ++i) {
    cust[i].clear();
  }
  for (int i = 0; i < M; ++i) {
    int a, b;
    cin >> a >> b;
    cust[b].push_back(a);
    if (cust[b].size() > mr)
      mr = cust[b].size();
    cnt[a]++;
  }
  
  for (int i = 1; i <= N; ++i) {
    sum[i] += sum[i-1] + cnt[i];
    if (i * mr < sum[i]) {
      mr = sum[i] / i;
      if (sum[i] % i) {
        ++mr;
      }
    }
  }
  for (int i = 1; i <= N; ++i) {
    if (cnt[i] > mr) {
      ans2 += cnt[i] - mr;
    }
  }
  cout << mr << ' ' << ans2 << endl;
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
