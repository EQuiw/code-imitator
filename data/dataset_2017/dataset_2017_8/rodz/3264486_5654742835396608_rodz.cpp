#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;


map<ll, ll> memo;

ll cnt(ll x, ll mi, ll ma)
{
	if (x == 0)
		return 0;

	ll l = (x-1)/2, r = x/2;
	if (min(l, r) < mi or min(l, r) == mi and max(l, r) < ma)
		return 0;
	
	if (memo.count(x))
		return memo[x];

	return memo[x] = 1 + cnt(l, mi, ma) + cnt(r, mi, ma);
}

int main()
{
	int t, casecnt = 1;
	cin >> t;
	while(t--)
	{
		ll n, k;
		cin >> n >> k;
		ll lo = 0, hi = (n-1)/2;
		while (lo < hi)
		{
			ll mid = (lo+hi+1)/2;
			memo.clear();
			ll c = cnt(n, mid, 0);
			//printf("mi = %lld, c = %lld\n", mid, c);
			if (c >= k)
				lo = mid;
			else
				hi = mid-1;
		}
		ll mi = lo;

		lo = mi, hi = n/2;

		while (lo < hi)
		{
			ll mid = (lo+hi+1)/2;
			memo.clear();
			ll c = cnt(n, mi, mid);
			if (c >= k)
				lo = mid;
			else
				hi = mid-1;
		}

		printf("Case #%d: %lld %lld\n", casecnt++, lo, mi);
	}
	return 0;
}


