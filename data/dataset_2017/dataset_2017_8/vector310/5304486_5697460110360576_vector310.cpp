#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define rep(i, l, r) for(int i = l; i <= r; ++i)
using namespace std;
int n, m, flag, tot;
int t[101], s[101][101], cnt[51];
struct data{
	int a, l, r;
	data(){}
	data(int a, int l, int r):a(a), l(l), r(r){}
	bool operator < (const data &x)const{
		return r > x.r;
	}
}g[1010];
bool cmp(const data &x, const data &y){
	return x.l < y.l;
}
priority_queue<data> que[101]; 
int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int T, ans;
	cin >> T;
	rep(cas, 1, T){
		cin >> n >> m;
		tot = ans = 0;
		rep(i, 1, n) 
			while(!que[i].empty()) que[i].pop();
		rep(i, 1, n)
			scanf("%d", &t[i]);
		rep(i, 1, n)
			rep(j, 1, m)
				scanf("%d", &s[i][j]);
		rep(i, 1, n)
			rep(j, 1, m)if(s[i][j]){
				int r = floor((double)s[i][j] / (0.9*t[i]));
				int l = ceil((double)s[i][j] / (1.1*t[i]));
				if(l == 0) l = 1;
				if(l <= r)g[++tot] = data(i, l, r);
				//printf("s = %d l = %d r = %d\n", s[i][j], l, r);
			}
		sort(g + 1, g + tot + 1, cmp);
		rep(i, 1, tot){
			//printf("g[%d] = (%d %d %d)\n", g[i].a, g[i].l, g[i].r);
			rep(j, 1, n)
				while(!que[j].empty() && que[j].top().r < g[i].l) que[j].pop();
			que[g[i].a].push(g[i]);
			int minvalue = 1 << 29;
			rep(j, 1, n)
				if(que[j].size() < minvalue)
					minvalue = que[j].size();
			ans += minvalue;
			rep(j, 1, n)
				for(int k = 1; k <= minvalue; ++k)
					que[j].pop();
		}
		printf("Case #%d: %d\n", cas, ans);
	} 
	return 0;
}
 
