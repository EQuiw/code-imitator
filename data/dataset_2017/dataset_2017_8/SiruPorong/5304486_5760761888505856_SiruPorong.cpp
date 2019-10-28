#include<stdio.h>

int n,m;
char mp[26][26];

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int t,i,j,k;
	scanf("%d",&t);

	for(int tt=1;tt<=t;tt++)
	{
		scanf("%d%d",&n,&m);

		for(i=1;i<=n;i++)
		{
			scanf(" %s",mp[i]+1);
		}
		bool a ;
		for(i=1;i<=n;i++)
		{
			a=false;
			for(j=1;j<=m;j++)
			{
				if(mp[i][j]!='?')
				{
					a=true;
					for(k=j-1;k>=1;k--)
					{
						if(mp[i][k]!='?')
							break;
						mp[i][k]=mp[i][j];
					}
					for(k=j+1;k<=m;k++)
					{
						if(mp[i][k]!='?')
							break;
						mp[i][k]=mp[i][j];
					}
				}
			}
		}
		for(i=1;i<=n;i++)
		{
			if(mp[i][1]!='?')
			{
				for(j=i-1;j>=1;j--)
				{
					if(mp[j][1]!='?')break;

					for(k=1;k<=m;k++)
					{
						mp[j][k]=mp[j+1][k];
					}
				}
				for(j=i+1;j<=n;j++)
				{
					if(mp[j][1]!='?')break;

					for(k=1;k<=m;k++)
					{
						mp[j][k]=mp[j-1][k];
					}
				}
			}
		}

		printf("Case #%d:\n",tt);
		for(i=1;i<=n;i++)
			printf("%s\n",mp[i]+1);
	}
	return 0;
}