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
typedef pair<tint,tint> par;


par h[1100];

int main()
{
	freopen("test.txt","r",stdin);
	freopen("out.txt","w",stdout);

	int t,n,d; cin >> t;

	forsn(caso,1,t+1)
	{
		cin >> d >> n;
		forn(i,n) cin >> h[i].x >> h[i].y;
		sort(h,h+n);

		int next = n-1;

		for(int i = (n-2); i >= 0; i--)
		{
			//cout << h[i].x << " " << h[i].y << endl;
			if(h[i].y > h[next].y)
			{
				par q = mp(h[next].x - h[i].x, h[i].y - h[next].y);
				par arr = mp(d - h[next].x, h[next].y);
				//cout << i << " " << next << endl;
				//cout << q.x << " " << q.y << endl;
				//cout << arr.x << " " << arr.y << endl;
				if(q.x * arr.y >= q.y * arr.x)
				{
					next = i;
				}
			}
			else next = i;
		}
		//cout << next << endl;

		par arr = mp(d - h[next].x, h[next].y);
		double ans = d * arr.y / (arr.x + 0.0);
		cout.setf(ios::showpoint | ios::fixed);
		cout.precision(10);

		cout << "Case #" << caso << ": " << ans << endl;
	}

	return 0;
}