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
#define EPS 1e-8

using namespace std;

typedef pair<int,int> par;
typedef long long int tint;
map<char,char> inv;

int main()
{
	freopen("test.txt","r",stdin);
	freopen("out.txt","w",stdout);
	
	inv['-'] = '+'; inv['+'] = '-';
	int t,k; string s;

	cin >> t;

	forsn(caso,1,t+1)
	{
		cin >> s >> k;
		int l = s.size();

		int ans = 0;
		forn(i, l + 1 - k)
		{
			if(s[i] == '-')
			{
				forsn(j,i,i+k) s[j] = inv[s[j]];
				ans++;
			}
		}
		bool check = true;
		forn(i,l)
		{
			check = check and s[i] == '+';
		}
		cout << "Case #" << caso << ": ";
		if(check) cout << ans << endl;
		else cout << "IMPOSSIBLE" << endl;
	}

	return 0;
}