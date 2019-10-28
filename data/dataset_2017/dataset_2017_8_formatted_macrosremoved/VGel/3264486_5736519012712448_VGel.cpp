#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
const int maxn = 1010;
int n, K, len;
char str[maxn];
int dir[maxn], f[maxn];
int calc() {
  memset(f, 0, sizeof(f));
  int res = 0, sum = 0;
  for (int i = 0; i + K <= len; i++) {
    //        cout<<i<<" "<<((dir[i]+sum)&1)<<" "<<f[i]<<" "<<sum<<endl;
    if ((dir[i] + sum) & 1)
      res++, f[i] = 1, sum++;
    //        cout<<f[i]<<" "<<sum<<endl;
    if (i - K + 1 >= 0)
      sum -= f[i - K + 1];
  }
  for (int i = len - K + 1; i < len; i++) {
    //        cout<<i<<" "<<((dir[i]+sum)&1)<<" "<<f[i]<<" "<<sum<<endl;
    if ((dir[i] + sum) & 1)
      return -1;
    //        cout<<f[i]<<" "<<sum<<endl;
    if (i - K + 1 >= 0)
      sum -= f[i - K + 1];
  }
  return res;
}

int main() {
  //    freopen("A-small-attempt3.in","r",stdin);
  //    freopen("A-small-attempt3.out","w",stdout);
  int T_T;
  scanf("%d", &T_T);
  for (int T = 1; T <= T_T; T++) {
    scanf("%s", str);
    len = strlen(str);
    for (int i = 0; i < len; i++)
      dir[i] = (str[i] == '-') ? 1 : 0;
    //        for (int i=0;i<len;i++) cout<<dir[i];cout<<endl;
    scanf("%d", &K);
    int ans = calc();
    if (ans == -1)
      printf("Case #%d: IMPOSSIBLE\n", T);
    else
      printf("Case #%d: %d\n", T, ans);
  }
  return 0;
}
