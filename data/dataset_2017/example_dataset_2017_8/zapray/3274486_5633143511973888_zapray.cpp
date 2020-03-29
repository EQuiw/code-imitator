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

int main() {
	int T;
	cin >> T;	
	for (int cs = 1; cs <= T; cs++) {
		printf("Case #%d: ", cs);
		
		int n, k;
		cin >> n >> k;
		

		double x;

		cin >> x;
		int u = round(x * 10000);
		vector<int> p;

		for (int i = 0; i < n; i++) {
			cin >> x;
			p.push_back(round(x * 10000));
		}
		p.push_back(10000);

		sort(p.begin(), p.end());
		
		for (int i = 1; i < p.size(); i++) {
			if (p[i] > p[i - 1]) {
				int diff = p[i] - p[i - 1];
				if (u >= diff * i) {
					u -= diff *i;
					for (int j = 0; j < i; j++) p[j] = p[i];
				}
				else {
					int q = u / i;
					for (int j = 0; j < i; j++) p[j] += q;
					u -= q*i;
					if (u) {
						for (int j = 0; j < u; j++) p[j] += 1;
					}
					break;
				}
			}
		}

		double ans = 1;
		for (int i = 0; i < p.size() - 1; i++) {
			ans *= double(p[i]) / 10000;
		}
		printf("%.8lf\n", ans);
	}
	return 0;
}