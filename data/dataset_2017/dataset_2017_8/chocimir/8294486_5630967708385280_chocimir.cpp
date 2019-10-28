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

#define dprintf(...) fprintf(stderr, __VA_ARGS__)

int cond = 1;
#define DB(X) {if(cond){cerr<<"Line:"<<__LINE__<<", "<<#X<<" = "<<X<<endl;}}

double solve() {
	double d; int n; cin >> d >> n;
	double tmax = 0.;
	for(int i = 0; i < n; ++i) {
		double k, s; cin >> k >> s;
		if (k < d) {
			double t = (double) (d - k) / s;
			tmax = t > tmax ? t : tmax;
		}
	}
	return d / tmax;
}

int main() {
	int t; cin >> t;
	for(int x = 1; x <= t; ++x){

		cout.precision(9);
		cout << "Case #" << x << ": " << fixed <<  solve() << endl;//result 
	}
	return 0;
}
