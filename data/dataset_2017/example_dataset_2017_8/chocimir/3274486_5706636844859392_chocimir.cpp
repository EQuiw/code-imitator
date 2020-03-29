#include<algorithm>
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

int solve() {
	int ac, aj; cin >> ac >> aj;
	vector<pair<pair<int, int>, int> > as;
	int cjl[2] = {720, 720};
	FOR(i, 0, ac) {
		int c, d; cin >> c >> d;
		as.push_back({{c, d}, 0});
		cjl[0] -= (d-c);
	}
	FOR(i, 0, aj) {
		int c, d; cin >> c >> d;
		as.push_back({{c, d}, 1});
		cjl[1] -= (d-c);
	}

	int res = 0;
	sort(as.begin(), as.end());
	as.push_back({{24*60 + as[0].first.first, 24*60 + as[0].first.second}, as[0].second});
	vector<int> le[2];
	FOR(i,0, as.size() - 1) {
		if (as[i].second == as[i+1].second) {
			res += 2;
			le[as[i].second].push_back(as[i+1].first.first - as[i].first.second);
		}
		else {
			res += 1;
		}
	}
	FOR(i,0,2) {
		sort(le[i].begin(), le[i].end());
		FOR(j,0,le[i].size()) {
			if (cjl[i] >= le[i][j]) {
				cjl[i] -= le[i][j];
				res -= 2;
			}	
		}
	}

	return res;
}

int solve2() {
	
	int ac, aj; cin >> ac >> aj;
	vector<pair<int, int> > as;
	int cjl[2] = {720, 720};
	FOR(i, 0, ac) {
		int c, d; cin >> c >> d;
		as.push_back({c, d});
		cjl[0] -= (d-c);
	}
	FOR(i, 0, aj) {
		int c, d; cin >> c >> d;
		as.push_back({c, d});
		cjl[1] -= (d-c);
	}

	sort(as.begin(), as.end());
	if (ac == aj) {
		return 2;
	}
	
	if (ac + aj == 1) {
		return 2;
	}
	
	if (as[1].second - as[0].first <= 720) {
		return 2;
	}

	if (24*60 + as[0].first - as[1].second <= 720) {
		return 2;
	}

	return 4;
}

int main() {
	int t; cin >> t;
	for(int x = 1; x <= t; ++x){
		cout << "Case #" << x << ": " << solve() << endl;//result 
	}
	return 0;
}
