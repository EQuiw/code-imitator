#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int Ad, Hd, Ak, Hk, B, D;
//    Hd   Hk   Ad
char s[102][102][102][102];

class d{
public:
  int h1,h2,a1,a2,sp;
} q[2000000];

int main(void){
    int t;
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
        scanf("%d%d%d%d%d%d",&Hd,&Ad,&Hk,&Ak,&B,&D);

        /*
        if (Ak-D >= Hd) {
          printf("Case #%d: IMPOSSIBLE\n", tt);
          continue;
        }
        */

        int ans = -1;

        s[Hd][Hk][Ad][Ak] = 1;
        q[0] = (d){Hd, Hk, Ad, Ak, 0};
        int st=0,ed=1;
        for(;st<ed;++st){
          if (q[st].h2 <= q[st].a1){
            ans = q[st].sp+1;
            break;
          }

          int h1 = q[st].h1;
          int h2 = q[st].h2;
          int a1 = q[st].a1;
          int a2 = q[st].a2;
          int sp = q[st].sp;
          // printf("%d %d %d %d %d\n",h1,a1,h2,a2,sp);
          if (Hd>a2 && !s[Hd-a2][h2][a1][a2]) {
            q[ed]=(d){Hd-a2, h2, a1, a2, sp+1};
            s[Hd-a2][h2][a1][a2]=1;
            ++ed;
          }

          if (h1>a2 && !s[h1-a2][h2-a1][a1][a2]) {
            q[ed]=(d){h1-a2, h2-a1, a1, a2, sp+1};
            s[h1-a2][h2-a1][a1][a2]=1;
            ++ed;
          }

          int ab = min(a1+B, 101);
          if (h1>a2 && !s[h1-a2][h2][ab][a2]) {
            q[ed]=(d){h1-a2, h2, ab, a2, sp+1};
            s[h1-a2][h2][ab][a2]=1;
            ++ed;
          }

          int ad = max(a2-D, 0);
          if (h1>ad && !s[h1-ad][h2][a1][ad]) {
            q[ed]=(d){h1-ad, h2, a1, ad, sp+1};
            s[h1-ad][h2][a1][ad]=1;
            ++ed;
          }

        }

        if (ans < 0) {
          printf("Case #%d: IMPOSSIBLE\n", tt);
          continue;
        }
        printf("Case #%d: %d\n", tt, ans);
    }
    return 0;
}

