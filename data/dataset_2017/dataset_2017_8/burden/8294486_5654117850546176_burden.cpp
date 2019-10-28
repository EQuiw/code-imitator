#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const char s[7]={' ','R','B','Y','G','O','V'};
int n,m,t,a[10],ans[2000];

int main()
{
    //freopen("b.in","r",stdin);
    //freopen("b.out","w",stdout);
    int T,w=0;
    for (scanf("%d",&T); T--; )
    {
        //scanf("%d%d%d%d%d%d",&R,&O,&Y,&G,&B,&V);
        scanf("%d%d%d%d%d%d%d",&n,&a[1],&a[5],&a[3],&a[4],&a[2],&a[6]);
        m=0;
        bool flag=true;
        if (a[1]>0) ans[++m]=s[1],a[1]--,t=1; else
            if (a[2]>0) ans[++m]=s[2],a[2]--,t=2; else ans[++m]=s[3],a[3]--,t=3;
        while (a[1]>0 || a[2]>0 || a[3]>0)
        {
            int x=t+1,y=t-1;
            if (x>3) x=1;
            if (y==0) y=3;
            if (a[x]==0 && a[y]==0) {flag=false; break;}
            if (a[x]>a[y] || a[x]==a[y] && s[x]==s[1]) ans[++m]=s[x],a[x]--,t=x; else ans[++m]=s[y],a[y]--,t=y;
            //printf("%d %d %d\n",a[1],a[2],a[3]);
        }
        if (ans[1]==ans[m]) flag=false;
        printf("Case #%d: ",++w);
        if (!flag) printf("IMPOSSIBLE\n"); else
        {
            for (int i=1; i<=m; i++) printf("%c",ans[i]);
            printf("\n");
        }
    }
    return 0;
}
