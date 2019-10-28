#include <bits/stdc++.h>

using namespace std;

string s;
int k,n;
int a[1010];
int T;
int ans;

int main()
{
	freopen("as.in","r",stdin);
	freopen("as.out","w",stdout);
	cin >> T;
	for(int ii = 1; ii <= T; ii++)
	{
		cin >> s >> k;
		n = s.length();
		ans = 0;
		for(int i = 0; i < n; i++)
			if(s[i] == '-')
				a[i] = 0;
			else
				a[i] = 1;
		for(int i = 0; i < n; i++)
		{
			if(!a[i])
			{
				if(i+k > n)
				{
					ans = -1;
					break;
				}
				ans++;
				for(int j = i; j < i+k; j++)
					a[j] = 1 - a[j];
			}
		}
		printf("Case #%d: ",ii);
		if(ans == -1)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}

