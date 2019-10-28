#include <bits/stdc++.h>


#define debug(x) cerr<< #x << ": "<< x << endl;
#define print(x) cerr<< x << endl;

#define mp make_pair
#define pb push_back
#define all(x) (x).begin() , (x).end()
#define rall(x) (x).rbegin() , (x).rend()
#define REP(i,x,y) for(int i=x;i<y;i++)
#define REPIT(it,A) for(typeof(A.begin()) it = (A.begin()); it!=A.end();it++)
#define fst first
#define snd second
#define sqr(x) ((x)*(x))

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);
#define ones(x) __builtin_popcountll(x)
using namespace std;

typedef pair<int,int> ii ;
typedef long long ll ;
typedef vector<int> vi;
typedef vector<ii> vii;


// Fast O(|V|^3) flow, works for n ~ 5000 with no problem
// Actual flow values in edges with cap > 0 (0 cap = residual)

typedef long long LL;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
  int N;
  vector<vector<Edge> > G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : 
	N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

	void Enqueue(int v) { 
		if (!active[v] && excess[v] > 0) { 
			active[v] = true; Q.push(v); 
		} 
	}

  void Push(Edge &e) {
    int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;    
    excess[e.from] -= amt;
    Enqueue(e.to);
  }
  
  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < G[v].size(); i++) 
      if (G[v][i].cap - G[v][i].flow > 0)
	dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

	void Discharge(int v) {
	for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) 
		Push(G[v][i]);
	if (excess[v] > 0) {
		   if (count[dist[v]] == 1) Gap(dist[v]); 
		   else Relabel(v);
		}
	}

  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }
    
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }
    
    LL totflow = 0;
    for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};



ll q[55][55];
ll r[55];
int n, p;
typedef pair<ll,ll> pll;

bool cross(pll a, pll b){
    if(a.snd < b.fst) return false;
    if(a.fst > b.snd) return false;
    return true;
}

int main(){
   fastio;
   int ntest;
	cin >> ntest;
	REP(test,1,ntest+1){
		cout<<"Case #"<<test<<": ";
		cin >> n >> p;
		REP(i,0,n){
			cin >> r[i];
		}
		REP(i,0,n){
			REP(j,0,p){
				cin >> q[i][j];
			}
		}
		
		
		
		vector<vector<pair<ll,ll> > > data(n);
	
		REP(i,0,n){
			REP(j,0,p){
				ll num = 10*q[i][j];
				ll denom = 11*r[i];
				ll lo = num % denom == 0 ? num / denom : num / denom + 1;
				denom = 9*r[i];
				ll hi = num / denom;
				if(lo <= hi){
					data[i].pb(mp(lo,hi));
				}
			}
			
		}
		if(n == 1){
		    cout<<data[0].size()<<endl;
		    continue;
		}
		PushRelabel pr = PushRelabel(2*p + 3);
		int source = 2*p+1;
		int sink = source + 1;
        REP(i,0,data[0].size()){
            REP(j,0,data[1].size()){
                if(cross(data[0][i],data[1][j])){
                    pr.AddEdge(i,j+p,1);
                }
            }
            pr.AddEdge(source,i,1);
        }
        REP(i,0,data[1].size()) pr.AddEdge(i+p,sink,1);
        
	    
		cout<<pr.GetMaxFlow(source,sink)<<endl;
	}
   return 0;
}

