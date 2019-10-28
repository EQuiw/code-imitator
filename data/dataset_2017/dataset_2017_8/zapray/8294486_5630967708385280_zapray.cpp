#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <queue>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unordered_set>
#include <unordered_map>


using namespace std;
typedef double ll;
#define MODD(a,b) (((a)%(b)+(b))%(b))
#define EPS 1E-5
#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

using namespace std;


double arrive[1005];


int main() {
	int T; cin >> T;
	for (int cs = 1; cs <= T; cs++) {
		int  D, N;
		cin >> D >> N;

		vector<pair<ll, ll> > h;
		for (int i = 0; i < N; i++) {
			ll k, s;
			cin >> k >> s;
			h.push_back(make_pair(k,s));
		}

		sort(h.begin(), h.end());
		int i = N - 1;
		double last = 0;
		for (i = N - 1; i >= 0; i--) {
			arrive[i] = double(D - h[i].first) / h[i].second;
			last = max(last, arrive[i]);
		}
		printf("Case #%d: %.6lf\n", cs, D/ last);
		
	}
	return 0;
}