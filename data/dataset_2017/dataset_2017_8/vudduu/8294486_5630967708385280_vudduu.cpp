// vudduu - codejam 2017 round 1 B
// Problem A
#include <iostream>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <functional>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <stdio.h>
#include <string.h>
using namespace std;

#define FOR(i,a,b)  for(int i=(a),_##i=(b);i<_##i;++i)
#define F(i,a)      FOR(i,0,a)
#define ALL(x)      x.begin(),x.end()
#define PB          push_back
#define MP          make_pair
#define S           size()
typedef long long   LL;

double D, N;
vector<pair<int, int> > hs;

double getTime(double K, double V) {
    return (D - K) / V;
}

void solve() {
    cin >> D >> N;
    hs.resize(N);
    F(i, N) cin >> hs[i].first >> hs[i].second;
    sort(hs.rbegin(), hs.rend());
    double maxiK = hs[0].first;
    double maxiV = hs[0].second;
    double maxiT = getTime(hs[0].first, hs[0].second);
    F(i, N) {
        double t = getTime(hs[i].first, hs[i].second);
        if (t > maxiT) {
            maxiT = t;
            maxiK = hs[i].first;
            maxiV = hs[i].second;
        }
        else {
            maxiK = hs[i].first;
            maxiV = (D - maxiK) / maxiT;
        }
    }
    maxiV = D / maxiT;
    printf("%.8lf\n", maxiV);
}

int main() {
	int T;
    scanf("%d", &T);
    for(int cas=1; cas<=T ;cas++) {
        printf("Case #%d: ", cas);
        solve();
    }
}
