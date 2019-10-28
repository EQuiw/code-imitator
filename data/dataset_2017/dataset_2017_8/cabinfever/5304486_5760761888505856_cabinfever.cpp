#include <bits/stdc++.h>

using namespace std;

int r,c,T;
char s[30][30];
bool vis[30];

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	cin >> T;
	for(int ii = 1; ii <= T; ii++)
	{
		cin >> r >> c;
		memset(vis,0,sizeof(vis));
		for(int i = 0; i < r; i++)
		{
			scanf("%s",s[i]);
			bool check = false;
			for(int j = 0; j < c; j++)
				if(s[i][j] != '?')
				{
					check = true;
					int k = j - 1;
					while(k >= 0 && s[i][k] == '?')
						s[i][k] = s[i][j],k--;
					k = j+1;
					while(k < c && s[i][k] == '?')
						s[i][k] = s[i][j],k++;
				}
			if(check)
			{
				vis[i] = 1;
				int k = i - 1;
				while(k >= 0 && !vis[k])
				{
					for(int j = 0; j < c; j++)
						s[k][j] = s[i][j];
					vis[k] = 1;
					k--;
				}
			}
			else
			{
				if(i > 0 && vis[i-1])
				{
					for(int j = 0; j < c; j++)
						s[i][j] = s[i-1][j];
					vis[i] = 1;
				}
			}
		}
		printf("Case #%d:\n",ii);
		for(int i = 0; i < r; i++)
			printf("%s\n",s[i]);
	}
	return 0;
}

