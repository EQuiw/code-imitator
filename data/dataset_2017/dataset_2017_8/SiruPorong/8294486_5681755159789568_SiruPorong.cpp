#include<stdio.h>
#include<algorithm>

using namespace std;

int n,m,mp[101][101];
pair<int,double> h[101];
double dist[101];

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
			scanf("%d%lf",&h[i].first,&h[i].second);
			dist[i]=-1;
		}

		for(i=1;i<=n;i++)for(j=1;j<=n;j++){
				scanf("%d",&mp[i][j]);
		}
		int a,b;
		for(i=1;i<=m;i++)scanf("%d%d",&a,&b);
		double c;
		dist[1]=0;
		for(i=1;i<=n;i++)
		{
			c=0;
			for(j=i+1;j<=n;j++)
			{
				c+=mp[j-1][j];
				if(c>h[i].first)break;

				if(dist[j]==-1||dist[j]>dist[i]+c/h[i].second)
				{
					dist[j] = dist[i]+c/h[i].second;
				}
			}
		}

		printf("Case #%d: %lf\n",tt,dist[n]);
	}
	return 0;
}