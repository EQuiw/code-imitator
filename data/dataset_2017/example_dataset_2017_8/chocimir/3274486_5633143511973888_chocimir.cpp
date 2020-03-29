#include<algorithm>
#include<iomanip>
#include<cassert>
#include<cctype>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<deque>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

typedef long long LL;
typedef long double LD;

#define FOR(k,a,b) for(__typeof(a) k=(a); k < (b); ++k)
#define dprintf(...) fprintf(stderr, __VA_ARGS__)

int cond = 1;
#define DB(X) {if(cond){cerr<<"Line:"<<__LINE__<<", "<<#X<<" = "<<X<<endl;}}

double solve() {
	int n, k; cin >> n >> k;
	double u; cin >> u;
	vector<double> p;
	FOR(i,0,n) {
		double pi; cin >> pi;
		p.push_back(pi);
	}
	sort(p.begin(), p.end());
	
	p.push_back(1.);
	FOR(i,0,n) {
		double mu = (p[i+1]-p[i])*(i+1);
		if (mu <= u) {
			FOR(j,0,i+1) {
				p[j] += p[i+1] - p[i];
			}
			u -= mu;
		}
		else {
			FOR(j,0,i+1) {
				p[j] += u/(i+1);
			}
			u = 0.;
			break;
		}
	}

	if (u > 0) {
		FOR(i,0,n) {
			p[i] = min(1.,p[i] + u/n);
		}
	}

	double res = 1.;
	FOR(i, 0, n) {
		res *= p[i];
	}
	return res;

}

int main() {
	int t; cin >> t;
	for(int x = 1; x <= t; ++x){
		cout << "Case #" << x << ": " << setprecision(16) << fixed << solve() << endl;//result 
	}
	return 0;
}
