#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

#define LL long long
#define maxn 110

int N, Q;
LL E[maxn], S[maxn], dis[maxn][maxn];
double dist[maxn];
bool vis[maxn], inq[maxn];

double spfa(int s, int t){
	memset(inq, false, sizeof(inq)); memset(vis, false, sizeof(vis));
	vis[s] = true, dist[s] = 0, inq[s] = true;
	queue<int>q; q.push(s);
	while(!q.empty()){
		int p = q.front(); q.pop();
		inq[p] = false;
		for(int x = 1; x <= N; x++) if(p != x){
			if(dis[p][x] == -1 || dis[p][x] > E[p]) continue;
			double tmp = 1.0 * dis[p][x] / S[p];
			if (!vis[x] || dist[x] > dist[p] + tmp){
				vis[x] = true, dist[x] = dist[p] + tmp;
				if (!inq[x]){
					q.push(x); inq[x]=true;
				}
			}
		}
	}
	return dist[t];
}

int main(){
	freopen("C-small-attempt0.in","r",stdin);
	freopen("C-small-attempt0.out","w",stdout);
	int T, cnt = 0;
	scanf("%d", &T);
	while(T--) {
        scanf("%d%d", &N, &Q);
        for(int i = 1; i <= N; i++) scanf("%lld%lld", &E[i], &S[i]);
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                scanf("%lld", &dis[i][j]);
        for(int k = 1; k <= N; k++)
            for(int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++) {
                    if (dis[i][k] == -1 || dis[k][j] == -1) continue;
                    if (dis[i][j] == -1 || dis[i][j] > dis[i][k] + dis[k][j]) dis[i][j] = dis[i][k] + dis[k][j];
                }
        printf("Case #%d: ", ++cnt);
        for(int i = 1, u, v; i <= Q; i++){
            scanf("%d%d", &u, &v);
            printf("%.8lf ", spfa(u, v));
        }
        printf("\n");
	}
}
