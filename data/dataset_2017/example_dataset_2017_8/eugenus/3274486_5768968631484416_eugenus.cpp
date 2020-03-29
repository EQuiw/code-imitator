#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <set>

#define forn(i,n) for(int i = 0; i < (n); i++)
#define forsn(i,s,n) for(int i = (s); i < (n); i++)
#define all(v) ((v).begin, (v).end)
#define pb push_back
#define x first
#define y second
#define mp make_pair
#define PI acos(-1)

using namespace std;

typedef long long int tint;
typedef pair<tint,tint> par;

par pan[1100];
pair<tint, par> info[1100];

tint dp[1100][1100];

tint sq(tint a)
{
	return ((a)*(a));
}

tint area(par a)
{
	tint ans = sq(a.x) + 2l * a.x * a.y;

	return (ans);
}

int main()
{
	freopen("test.txt","r",stdin);
	freopen("out2.txt","w",stdout);

	int t,n,k;
	cin >> t;

	cout.setf(ios::showpoint | ios::fixed);
	cout.precision(10);

	forsn(caso,1,t+1)
	{
		cin >> n >> k;
		forn(i,n) forn(j,n) dp[i][j] = 0;
		forn(i,n) cin >> pan[i].x >> pan[i].y;
		sort(pan, pan + n);

		tint ans = 0ll;

		forn(i,n) dp[i][1] = area(pan[i]);
		tint best[1100];
		tint be[1100];
		best[0] = dp[0][1] - sq(pan[0].x);
		for(int i = 1; i < n; i++)
		{
			tint cnd = (dp[i][1] - sq(pan[i].x));
			if( cnd > best[i-1])
			{
				best[i] = cnd;
			}
			else best[i] = best[i-1];
		}

		forsn(j,2,k+1)
		{
			dp[j-1][j] = area(pan[j-1]) + best[j-2];
			be[j-1] = dp[j-1][j] - sq(pan[j-1].x);
			//cout << dp[j-1][j] << " ";
			for(int i = j; i < n; i++)
			{
				dp[i][j] = area(pan[i]) + best[i-1];
				tint cnd = dp[i][j] - sq(pan[i].x);
				if(cnd > be[i-1]) be[i] = cnd;
				else be[i] = be[i-1];
				//cout << dp[i][j] << " ";
			}
			forn(i,n) best[i] = be[i];
		}
		forn(i,n)
		{
			ans = max(dp[i][k], ans);
		}

		cout << "Case #" << caso << ": " << ans * PI << endl;
	}

	return 0;
}