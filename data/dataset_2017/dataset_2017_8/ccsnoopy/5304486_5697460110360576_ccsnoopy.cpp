#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#ifdef DEBUG
    #define cek(x) cout<<x
#else
    #define cek(x) if(false){}
#endif // DEBUG

#define fi first
#define se second
#define INF 1000000000
#define INFLL 1000000000000000000LL
#define EPS 1e-9
#define PI acos(-1.0)
#define pb push_back
#define TC() while(tc--)
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORN(i,n) for(int i=0;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define REPN(i,a,b) for(int i=a;i<=b;i++)
#define reset(a,b) memset(a,b,sizeof(a))
#define ALL(v) v.begin(), v.end()
#define SORT(v) sort(ALL(v))
#define SORTA(v,n) sort(v, v + n)
#define SZ(v) (int) v.size()
#define sc(x) scanf("%d",&x)

int unit[52];
int wt[52][52];
int mn[52][52], mx[52][52];
int f;
vii adjList[1010];
int par[1010];
int n,p;

void open(){
	freopen("D:/OneDrive/Code/GCJ/B-small-attempt0 (1).in","r",stdin);
	freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

void augment(int x){
	if(par[x] != x){
		for(int i = 0; i < adjList[par[x]].size();i++){
			if(adjList[par[x]][i].first == x){
				f = min(f, adjList[par[x]][i].second);
				break;
			}
		}
		augment(par[x]);
		for(int i = 0;i < adjList[par[x]].size();i++){
			if(adjList[par[x]][i].first == x){
				adjList[par[x]][i].second -= f;
				break;
			}
		}

		for(int i = 0; i < adjList[x].size();i++){
			if(adjList[x][i].first == par[x]){
				adjList[x][i].second += f;
				break;
			}
		}
	}
}

int maxflow(){
	int mf = 0;
	f = 0;
	while(true){
		f = 0;
		reset(par, -1);
		queue<int> q;
		q.push(n*p);
		par[n*p] = n*p;
		bool found = false;

		while(!q.empty()){
			int node = q.front();
			// cout <<"cur : " << node << endl;
			q.pop();
			FOR(i,adjList[node].size()){

				int nx = adjList[node][i].first;
				int cap = adjList[node][i].second;
				// cout << nx << " " << cap << endl;
				if(cap > 0 && par[nx] == -1){
					par[nx] = node;
					if(nx == n*p + 1){
						f = INF;
						augment(nx);
						found = true;

						break;
					}
					q.push(nx);
				}
			}
			if(found)break;
		}

		if(f == 0)break;
		mf += f;
	}

	return mf;
}

int main(void){
	open();
	int tc;
	sc(tc);

	for(int ct = 1; ct <= tc; ct++){
		map<int,int> mp;
		
		sc(n);sc(p);
		FOR(i,n){
			sc(unit[i]);
		}
		
		reset(mn, -1);
		reset(mx, -1);

		FOR(i,n){
			FOR(j,p){
				sc(wt[i][j]);
				int tmp1 = floor(1.0 * wt[i][j] / (0.9 * unit[i]));
				int tmp2 = ceil(1.0 * wt[i][j] / (1.1 * unit[i]));
				int bawah = min(tmp1, tmp2);
				int atas = max(tmp1, tmp2);
				// cout << bawah << " " << atas << endl;
				while(bawah <= atas){
					if(bawah * 0.9 * unit[i] - EPS <= 1.0 * wt[i][j] && 1.0 * wt[i][j] <= bawah * 1.1 * unit[i] + EPS)break;
					else bawah++;
				}
				
				// cout << bawah << " " << atas << endl;

				if(bawah > atas)continue;

				while(atas >= bawah){
					if(atas * 0.9 * unit[i] - EPS<= 1.0 * wt[i][j] && 1.0 * wt[i][j] <= atas * 1.1 * unit[i] + EPS)break;
					else atas--;
				}
				// cout <<"idx : " << i << endl;
				// cout << bawah << " " << atas << endl;
				mn[i][j] = bawah;
				mx[i][j] = atas;

				// while(mx[i][j] == -1 && )

			}
		}

		FOR(i,1010)adjList[i].clear();

		FOR(i,n - 1){
			FOR(j,p){
				if(mn[i][j] <= 0)continue;
				FOR(k,p){
					if(mn[i + 1][k] <= 0)continue;
					// printf("%d %d %d %d\n", mn[i][j], mx[i][j], mn[i+1][k], mx[i+1][k]);
					if((mn[i][j] <= mn[i + 1][k] && mn[i + 1][k] <= mx[i][j]) || (mn[i + 1][k] <= mn[i][j] && mn[i][j] <= mx[i + 1][k])){
						// cout << (i * p + j) << " to " << ((i+1)*p + k) << endl;
						adjList[i * p + j].pb(ii((i+1)*p + k, 1));
						adjList[(i+1) * p + k].pb(ii(i * p + j, 0));
					}
				}
			}
		}

		FOR(j,p){
			//source + to sink.
			if(mn[0][j] > 0){
				adjList[n*p].pb(ii(j,1));
				adjList[j].pb(ii(n*p, 0));
			}
			
			if(mn[n-1][j] > 0){
				adjList[(n-1) * p + j].pb(ii(n*p + 1, 1));
				adjList[n*p + 1].pb(ii((n-1) * p + j, 0));
			}
			
		}

		printf("Case #%d: %d\n", ct, maxflow());
		cerr << "Test " << ct << " done \n";
	}
    return 0;
}


