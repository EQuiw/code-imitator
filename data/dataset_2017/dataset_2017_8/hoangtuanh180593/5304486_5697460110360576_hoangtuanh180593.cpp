#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define PII pair<int,int>
void mf(){
	// freopen("input.in","r",stdin);

	freopen("Bsmall3.in","r",stdin);
	freopen("Bsmall3.ou","w",stdout);

	//freopen("Blarge.in","r",stdin);
	//freopen("Blarge.ou","w",stdout);
}
int n,m;
ll a[57], c[57], b[57];
ll d[57][57];

const int maxn = 1e3 + 7;
struct Edge{
	int u,v, c, f, rid;
	Edge(int u, int v, int c, int f, int rid):
	u(u), v(v), c(c), f(f), rid(rid){}
};
struct maxFlow{

	int N, src, tar;	
	vector<vector<Edge>> ke;
	int prev[maxn] , prevId[maxn];

	maxFlow(int n, int src, int tar):
		N(n), src(src), tar(tar), ke(n + 1){};

	void addEdge(int u,int v,int c){
		int iu = ke[v].size(), iv = ke[u].size();
		ke[u].push_back(Edge(u, v, c, 0, iu));	
		ke[v].push_back(Edge(v, u, 0, 0, iv));
	}
	bool findPath(){
		for(int i = 1; i <= N; i++) prev[i] = -1;
		queue<int> q;
		q.push(src);prev[src] = src;prevId[src] = -1;
		while(!q.empty()){
			int x = q.front(); q.pop();
			for(int i = 0; i < ke[x].size(); i++){				
				Edge& e = ke[x][i];
				if(prev[e.v] != -1) continue;
				if(e.c > e.f){
					prev[e.v] = x;
					prevId[e.v] = i;
					//if(e.v == tar) return true;
					q.push(e.v);					
				}
			}
		}
		return prev[tar] != -1;
	}
	int getMaxFlow(){
		int ans = 0;
		while(findPath()){
			int res = 1e9, x = tar;
			int i = prev[x];			
			while(x!= src){//i->x				
				Edge& e = ke[i][prevId[x]];
				res = min(res, e.c - e.f);
				x = i; i = prev[x];
			}		
			ans += res;			
			//incFlow			
			x = tar; i = prev[x];
			while(x != src){//i->x
				Edge& e = ke[i][prevId[x]];				
				e.f += res;				
				Edge& re = ke[x][e.rid];
				re.f -= res;
				x = i; i = prev[x];
			}
		}
		///////////////
		return ans;
	}	
};

bool behon(double x, double y){
	if(x<=y) return true;
	// if(abs(x-y) <=1e-6) return true;
	return false;
}
ll form(ll b[]){	
	int mid, l = floor(b[1]*0.9f/a[1]), r= ceil(b[1]*1.1f / a[1]), rr= 0;	
	//cout<<l<<" "<<r<<endl;
	for(int i = l; i<= r; i++){
		bool ok = true;
		for(int j = 1; j<=n;j++){
			ll v = a[j]*i;
			if(behon(v*0.9f,b[j]) && behon(b[j], v*1.1f)) continue;
			ok = false;break;
		}
		if(ok) return 1;
	}	
	return 0;
}
int check(ll x, ll y){
	ll l = floor(x*0.9f/a[1]) - 1, r= ceil(x*1.1f / a[1]) + 1;
	//cout<<l<<" "<<r<<endl;
	for(int i =l; i<=r;i++){
		bool ok = true;
		ll a1 = a[1]*i, a2 = a[2]*i;
		if(behon(a1*0.9f, x) && behon(x, a1*1.1f)){
		}else ok = false;
		if(behon(a2*0.9f, y) && behon(y, a2*1.1f)){
		} else ok = false;
		if(ok) return 1;
	}
	return 0;
}
void solve(){
	cin>>n>>m;
	for(int i = 1;i<=n;i++) cin>>a[i];	
	for(int j = 1; j<=m; j++) cin>>b[j];
	if(n==1){
		int rr = 0;		
		for(int i = 1;i<=m;i++){
			ll l = floor(b[i]*0.9f/a[1]), r= ceil(b[i]*1.1f / a[1]);
			for(int j = l;j<=r;j++){
				ll v = j* a[1];
				if(behon(v*0.9f, b[i]) && behon(b[i],v*1.1f)){
					rr++;break;
				}
			}
		}
		cout<<rr<<endl;
		return;
	}
	for(int j = 1; j<=m; j++) cin>>c[j];

	for(int i = 1; i<=m;i++){
		for(int j = 1;j<=m;j++){			
			d[i][j] = check(b[i], c[j]);
		//	cout<<d[i][j]<<" ";
		}
		//cout<<endl;
	}

	int s = 1, t = m*2+2;
	maxFlow flow(t, s, t);
	for(int i = 1;i<=m;i++)
		flow.addEdge(s, i+1, 1);
	for(int i = 1;i<=m;i++)
		flow.addEdge(i+m+1, t, 1);
	for(int i =1;i<=m;i++)
		for(int j = 1;j<=m;j++){
			if(d[i][j]==1){
				flow.addEdge(i+1, j+m+1,1);
			}
		}	
	cout<<flow.getMaxFlow()<<endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	#ifdef tuanh
		mf();
	#endif
	int ntest;
	cin>>ntest;
	for(int nt = 1; nt <= ntest; nt++){
		cout<<"Case #"<<nt<<": ";
		solve();	
	}
	
	return 0;
}