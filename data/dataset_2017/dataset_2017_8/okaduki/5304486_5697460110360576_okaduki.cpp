#include <bits/stdc++.h>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;
using PII = pair<int, int>;
using LL = long long;
using VL = vector<LL>;
using VVL = vector<VL>;
using PLL = pair<LL, LL>;
using VS = vector<string>;

#define ALL(a)  begin((a)),end((a))
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define SZ(a) int((a).size())
#define SORT(c) sort(ALL((c)))
#define RSORT(c) sort(RALL((c)))

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define FF first
#define SS second
template<class S, class T>
istream& operator>>(istream& is, pair<S,T>& p){
  return is >> p.FF >> p.SS;
}
template<class S, class T>
ostream& operator<<(ostream& os, const pair<S,T>& p){
  return os << p.FF << " " << p.SS;
}
template<class T>
void maxi(T& x, T y){
  if(x < y) x = y;
}
template<class T>
void mini(T& x, T y){
  if(x > y) x = y;
}


const double EPS = 1e-10;
const double PI  = acos(-1.0);
const LL MOD = 1e9+7;

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int T; cin >> T;
  FOR(t_,1,T+1){
	int N, P; cin >> N >> P;
	VL rs(N);
	REP(i,N) cin >> rs[i];
	VVL qs(N, VL(P));
	REP(i,N){
	  REP(j,P)
		cin >> qs[i][j];
	  SORT(qs[i]);
	}

	LL ans = 0;
	if(N == 1){
	  REP(i,P){
		int lb_k = ceil(qs[0][i] * 1. / (rs[0] * 1.1));
		int ub_k = floor(qs[0][i] * 1. / (rs[0] * 0.9));
		if(lb_k <= ub_k)
		  ++ans;
	  }
	}
	else{
	  int i2 = 0;
	  REP(i1,P){
		int lb_k = ceil(qs[0][i1] * 1. / (rs[0] * 1.1));
		int ub_k = floor(qs[0][i1] * 1. / (rs[0] * 0.9));

		while(i2 < P){
		  int lb2_k = (int)ceil(qs[1][i2] * 1. / (rs[1] * 1.1));
		  int ub2_k = (int)floor(qs[1][i2] * 1. / (rs[1] * 0.9));
		  if(lb_k <= ub2_k && lb2_k <= ub_k){
			++ans;
			++i2;
			break;
		  }
		  else if(ub_k < lb2_k){
			break;
		  }
		  ++i2;
		}
	  }
	}

	cout << "Case #" << t_ << ": " << ans << endl;
  }

  return 0;
}
