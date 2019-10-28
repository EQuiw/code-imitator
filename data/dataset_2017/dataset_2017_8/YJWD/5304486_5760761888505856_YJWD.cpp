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
const int maxn = 1010;

int main() {
  //std::ios::sync_with_stdio(false);
  int i = 0, j = 0, k = 0, kase = 0;
  int n, t;
  char str[maxn];
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d",&t);
  while(t--)
  {
      int r, c;
      char cake[30][30];
      scanf("%d%d", &r, &c);
      getchar();
      fop(i, 0, r)
      {
          fop(j, 0, c)
          {
              scanf("%c", &cake[i][j]);
          }
          getchar();
      }
      int zero_flag = -1;
      bool meet_flag = false;
      fop(i, 0, r)
      {
          int cpos = -1;
          fop(j, 0, c)
          {
              if(cake[i][j]!='?')
              {
                  cpos = j;
                  break;
              }
          }
          if(cpos == -1)
          {
              if(!meet_flag)
              {
                  zero_flag++;
                  continue;
              }
              fop(j, 0, c)
              {
                  cake[i][j] = cake[i-1][j];
              }
          }
          else
          {
              meet_flag = true;
              fop(j, 0, cpos)
              {
                  cake[i][j] = cake[i][cpos];
              }
              fop(j, cpos+1, c)
              {
                  if(cake[i][j]=='?')
                    cake[i][j] = cake[i][j-1];
              }
          }
      }
      if(zero_flag>=0)
      {
          fome(i, zero_flag, 0)
          {
              fop(j, 0, c)
              {
                  cake[i][j] = cake[i+1][j];
              }
          }
      }
      printf("Case #%d:\n", ++kase);
      fop(i, 0, r)
      {
          fop(j, 0, c)
          {
              printf("%c", cake[i][j]);
          }
          printf("\n");
      }

  }



  return 0;
}
