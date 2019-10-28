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

using namespace std;

typedef long long int tint;
typedef pair<int,int> par;

tint d[110][110];
int e[110];
int s[110];
par qu[110];

double dp[110][110];

int main()
{
	freopen("test.txt","r",stdin);
	freopen("out2.txt","w",stdout);

	int t,n,q; cin >> t;

	forsn(caso,1,t+1)
	{
		cin >> n >> q;
		//cout << n << " " << q << endl;
		forn(i,n) cin >> e[i+1] >> s[i+1];
		forn(i,n)
		{
			forn(j,n) cin >> d[i+1][j+1];
		}
		forn(i,q)
		{
			cin >> qu[i].x >> qu[i].y;
		}
		tint acum[110]; acum[1] = 0;
		forn(i,110) forn(j,110) dp[i][j] = -1;
		dp[2][1] = d[1][2] / (s[1] + 0.0);
		forsn(i,2,n+1) acum[i] = acum[i-1] + d[i-1][i];
		//forn(i,n+1) cout << acum[i] << " ";
		//cout << endl;

		forsn(i,3,n+1)
		{
			forsn(j,1,i)
			{
				tint dis = (acum[i] - acum[j]);
				if(dis <= e[j] and dis >= 0)
				{
					double t = dis / (s[j] + 0.0);
					double m = -1;
					forsn(k,1,j)
					{
						if(dp[j][k] >= 0.0)
						{
							if(m > -1) m = min(m, dp[j][k]);
							else m = dp[j][k];
						}
					}
					if(m >= 0) dp[i][j] = t + m;
				}
			}
		}
		double ans = -1;
		forsn(i,1,n)
		{
			if(dp[n][i] >= 0.0)
			{
				if(ans >= 0.0) ans = min(ans, dp[n][i]);
				else ans = dp[n][i];
			}
		}

		cout.setf(ios::showpoint | ios::fixed);
		cout.precision(10);

		cout << "Case #" << caso << ": " << ans << endl;
	}

	return 0;
}