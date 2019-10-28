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
#include <sstream>

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

bool is_tidy(string s)
{
	int l = s.size();
	char cur = s[0];

	forsn(i,1,l)
	{
		if(cur > s[i]) return (false);
		cur = s[i];
	}

	return (true);
}

int main()
{
	freopen("test.txt","r",stdin);
	freopen("out.txt","w",stdout);

	int t,l;
	cin >> t;
	string n;

	forsn(caso,1,t+1)
	{
		cin >> n;
		l = n.size();
		vector<string> cnd;
		if(is_tidy(n)) cnd.pb(n);
		string acum = "";
		forn(i,l)
		{
			char c = (char)(n[i] - 1);
			string aux = acum + c;
			forsn(j,i+1,l) aux += '9';
			if(is_tidy(aux)) cnd.pb(aux);
			acum += n[i];
		}

		sort(cnd.begin(), cnd.end()); int u = cnd.size() - 1;
		int j = 0; while(cnd[u][j] == '0') j++;
		string ans = ""; forsn(k,j,cnd[u].size()) ans += cnd[u][k];

		cout << "Case #" << caso << ": " << ans << endl;
	}

	return 0;
}