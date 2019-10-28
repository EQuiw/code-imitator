#include <bits/stdc++.h>

using namespace std;
#define Fill(a, b) memset(a, b, sizeof(a))
#define Debug(x) cout << #x << "=" << (x) << endl;
#define fop(i, a, b) for (i = a; i < b; i++)
#define fope(i, a, b) for (i = a; i <= b; i++)
#define fom(i, a, b) for (i = a; i > b; i--)
#define fome(i, a, b) for (i = a; i >= b; i--)
typedef long long LL;
typedef pair<int, int> P;
const LL inf = 1LL << 61;
const LL mod = 1000000007;

int main() {
  std::ios::sync_with_stdio(false);
  int i = 0, j = 0, k = 0;
  int n, t, kase = 0;
  char str[30];
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d", &t);
  while(t--)
  {
    scanf("%s", str);
    n = strlen(str);
    for(i = 1; i < n; i++)
    {
      if(str[i]>=str[i-1])
      {
        continue;
      }
      else
        break;
    }
    if(i==n)
    {
      printf("Case #%d: %s\n", ++kase, str);
    }
    else
    {
      while(i>=1&&str[i-1]>str[i])
      {
        i--;
        str[i]--;
      }
      for( i++; i < n; i++)
      {
        str[i] = '9';
      }
      char ans[30];
      for(i = 0; i < n; i++)
      {
        if(str[i]!='0')
          break;
      }
      for(j = 0; i < n; j++, i++)
      {
        ans[j] = str[i];
      }
      ans[j] = '\0';
      printf("Case #%d: %s\n", ++kase, ans);
    }
  }

  return 0;
}
