#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int main()
{
	int t, casecnt = 1;
	cin >> t;
	while(t--)
	{
		string s;
		int k;
		cin >> s >> k;
		int ans = 0;
		for (int i = 0; i+k-1 < s.size(); i++)
		{
			if (s[i] == '-')
			{
				ans++;
				for (int j = 0; j < k; j++)
				{
					if (s[i+j] == '-')
						s[i+j] = '+';
					else
						s[i+j] = '-';
				}
			}
		}
		for (int i = 0; i < s.size() && ans != -1; i++)
		{
			if (s[i] == '-')
				ans = -1;
		}
		printf("Case #%d: ", casecnt++);
		if (ans != -1)
			printf("%d\n", ans);
		else
			printf("IMPOSSIBLE\n");
	}	
	return 0;
}


