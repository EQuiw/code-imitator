#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=60;
int n,m,point[maxn];
long long need[maxn],package[maxn][maxn],limit,ans,up,down;
inline void solve() {
    scanf("%d%d",&n,&m);
    for (int i=1; i<=n; i++)
        scanf("%lld",&need[i]);
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            scanf("%lld",&package[i][j]);
    for (int i=1; i<=n; i++)
        sort(package[i]+1,package[i]+1+m);
    int index=1;
    for (int i=2; i<=n; i++)
        if (package[i][m]/need[i]>package[index][m]/need[i]) index=i;
    for (int i=1; i<=n; i++)
        point[i]=1;
    limit=package[index][m]/need[index]+5;
    ans=0;
    for (long long k=1; k<=limit; k++) {
        bool flag=true;
        while (flag) {
            for (int i=1; i<=n; i++) {
                up=floor(1.1*need[i]*k);
                down=ceil(0.9*need[i]*k);
                while (point[i]<=m && package[i][point[i]]<=up && package[i][point[i]]<down)
                    point[i]++;
                if (point[i]>m || package[i][point[i]]>up) flag=false;
            }
            if (flag) {
                ans++;
                for (int i=1; i<=n; i++)
                    point[i]++;
            }
        }
    }
    printf("%lld\n",ans);
}
int main() {
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    for (int i=1; i<=T; i++) {
        printf("Case #%d: ",i);
        solve();
    }
    return 0;
}
