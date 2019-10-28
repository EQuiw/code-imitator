#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cassert>
using namespace std;

#define EPS 1e-12
#define ull unsigned long long
#define ll long long
#define VI vector<ll>
//#define PII pair<ll, ll> 
#define VVI vector<vector<ll> >
#define REP(i,n) for(int i=0,_n=(n);(i)<(int)_n;++i)
#define RANGE(i,a,b) for(int i=(int)a,_b=(int)(b);(i)<_b;++i)
#define RANGE_R(i,a,b) for(int i=(int)b-1,_a=(int)(a);(i)>=_a;--i)
#define MIN_UPDATE(target, value) target = min(target, value)
#define FOR(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)
#define ALL(c) (c).begin(), (c).end()
#define ALLR(c) (c).rbegin(), (c).rend()
#define PB push_back
#define MP(a, b) make_pair(a, b)
#define POPCOUNT(v) __builtin_popcountll((ll)(v))
#define IN_RANGE(v, a, b) ((a)<=(v) && (v)<(b))
#define CLEAR(table, v) memset(table, v, sizeof(table));
#define PRINT1(table, D0) REP(d0, D0) cout<<table[d0]<<" "; cout<<"\n";
#define PRINT2(table, D0, D1) REP(d0, D0) { REP(d1, D1) cout<<table[d0][d1]<<" "; cout<<"\n"; }
#define PRINT3(table, D0, D1, D2) REP(d0, D0) { REP(d1, D1) { REP(d2, D2) cout<<table[d0][d1][d2]<<" "; cout<<"\n"; } cout<<"\n"; }
#define DD(v) cout<<#v<<": "<<v<<endl
template <typename T0, typename T1> std::ostream& operator<<(std::ostream& os, const map<T0, T1>& v) { for( typename map<T0, T1>::const_iterator p = v.begin(); p!=v.end(); p++ ){os << p->first << ": " << p->second << " ";} return os; }
template <typename T0, typename T1> std::ostream& operator<<(std::ostream& os, const pair<T0, T1>& v) { os << v.first << ": " << v.second << " "; return os; }
template <typename T> std::ostream& operator<<(std::ostream& os, const vector<T>& v) { for( int i = 0; i < (int)v.size(); i++ ) { os << v[i] << " "; } return os; }
template <typename T> std::ostream& operator<<(std::ostream& os, const set<T>& v) { vector<T> tmp(v.begin(), v.end()); os << tmp; return os; }
template <typename T> std::ostream& operator<<(std::ostream& os, const deque<T>& v) { vector<T> tmp(v.begin(), v.end()); os << tmp; return os; }
template <typename T> std::ostream& operator<<(std::ostream& os, const vector<vector<T> >& v) { for( int i = 0; i < (int)v.size(); i++ ) { os << v[i] << endl; } return os; }


struct Dijkstra {
	struct edge{int to; double cost;};
	vector<vector<edge> > G;
	vector<double> V;
	const double Max = 1LL<<60;
	Dijkstra(int N) {
		G = vector<vector<edge> >(N);
		V = vector<double>(N, Max);
	}
	void add_edge(int v0, int v1, double cost) {
		if(v0<G.size() && v1<G.size()) G[v0].PB((edge){v1, cost});
	}
	typedef pair<double, ll> PII;
	ll run(int S, int E) {
		V[S]=0;
		priority_queue<PII> q;
		q.push(make_pair(0, S));
		while(q.size()) {
			PII el = q.top(); q.pop();
			if(el.second==E) break;
			if(-el.first > V[el.second]) continue;
			for(int i=0;i<(int)G[el.second].size();i++){
				const edge& e=G[el.second][i];
				if(V[e.to]>V[el.second]+e.cost){
					V[e.to]=V[el.second]+e.cost;
					q.push(make_pair(-V[e.to], e.to));
				}
			}
		}
		if(E<0) return -1;
		return V[E]==Max?-1:V[E];
	}
};

/*

*/
int main() {
	int test_cases;
	cin>>test_cases;
	ll N,Q;
	string s;
	REP(ttt, test_cases) {
		cin>>N>>Q;
		VI En(N), Sp(N);
		VVI dist(N, VI(N)); // [i][j] i->j
		REP(i, N) cin>>En[i]>>Sp[i];
		REP(i, N) REP(j, N) cin>>dist[i][j];
		ll dummy;
		cin>>dummy>>dummy;

		// node: (cityIdx, speedIdx)
		Dijkstra d(N*N);
		REP(i, N) {
			ll L = 0;
			RANGE(j, i+1, N) {
				L += dist[j-1][j];
				if(dist[j-1][j]==-1 || L > En[i]) break;

				double t = (double)L / Sp[i];
//				DD(i);DD(j);DD(t);
				// のりかえる
				d.add_edge(i*N+i, j*N+j, t);
				// のりかえない
				d.add_edge(i*N+i, j*N+i, t);
			}
		}
		d.run(0*N+0, -1);
		double ans = 1e100;
//		DD(d.V);
		REP(i, N) ans = min(ans, d.V[(N-1)*N+i]);

		printf("Case #%d: %.9f\n", ttt+1, ans);
//		return 0;
	}
	return 0;
}



