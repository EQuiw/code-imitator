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
#include <cassert>
#include <unordered_set>
#include <unordered_map>


using namespace std;
typedef long long ll;
#define MODD(a,b) (((a)%(b)+(b))%(b))
#define EPS 1E-5
#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

using namespace std;

#define PI 3.14159265358979323846


bool comp(pair<double, double>& x, pair<double, double>& y) {
	return x.first*x.second > y.first*y.second;
}

int main() {
	int T;
	cin >> T;	
	for (int cs = 1; cs <= T; cs++) {
		printf("Case #%d: ", cs);

		int k, n;
		cin  >> n >> k;

		vector<pair<double, double> > cakes;

		for (int i = 0; i < n; i++) {
			double r, h;
			cin >> r >> h;
			cakes.push_back(make_pair(r, h));
		}

		double ans = 0;
		for (int i = 0; i < n; i++) {
			double base_r = cakes[i].first;

			vector<pair<double, double> > candidates;
			for (int j = 0; j < n; j++) {
				if (j == i) continue;
				if (cakes[j].first <= base_r)
					candidates.push_back(cakes[j]);
			}
			if (candidates.size() < k - 1) continue;
		
			sort(candidates.begin(), candidates.end(), comp);
			
			double area = base_r * base_r * PI;
			area += 2 * PI * base_r * cakes[i].second;
			for (int j = 0; j < k - 1; j++) {
				area += 2 * PI * candidates[j].first * candidates[j].second;
			}

			ans = max(ans, area);
		}

		printf("%.9lf\n", ans);
	}
	return 0;
}