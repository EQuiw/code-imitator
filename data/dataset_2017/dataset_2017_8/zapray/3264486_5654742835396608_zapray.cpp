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
#include <unordered_map>


using namespace std;
typedef long long ll;
#define MODD(a,b) (((a)%(b)+(b))%(b))
#define EPS 1E-5
#define INF 1E9
#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

using namespace std;

pair<ll, ll> solve_small(ll n, ll k) {
	priority_queue<ll> Q;
	Q.push(n);
	for (ll i = 0; i < k-1; i++) {
		ll x = Q.top();
		Q.pop();
		Q.push((x - 1) / 2);
		Q.push(x / 2);
	}
	ll x = Q.top();
	return make_pair(x / 2, (x - 1) / 2);
}


int main()
{
	int T; cin >> T;
	for (int cs = 1; cs <= T; cs++) {
		ll n, k;
		cin >> n >> k;
		auto ans = solve_small(n, k);
		printf("Case #%d: %lld %lld\n", cs, ans.first, ans.second);
	}

	return 0;
}