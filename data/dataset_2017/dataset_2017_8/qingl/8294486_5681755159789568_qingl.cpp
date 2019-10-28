#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<string>
using namespace std;
typedef long long ll;
const int N = 105;
double e[N],s[N],d[N][N],t[N][N],r[N][N];
int main()
{
	freopen("C-small-attempt0.in","r",stdin);
	freopen("out.txt","w",stdout);
	int T,ca=1;
	scanf("%d",&T);
	while(T--)
	{
		printf("Case #%d:",ca++);
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)scanf("%lf%lf",&e[i],&s[i]);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)scanf("%lf",&d[i][j]);
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				for(int k=0;k<n;k++)if(i!=k&&i!=j&&k!=j&&d[j][i]!=-1&&d[i][k]!=-1)
				{
					double mi=d[j][i]+d[i][k];
					if(d[j][k]<0||d[j][k]>mi)d[j][k]=mi;
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(i!=j&&d[i][j]!=-1&&d[i][j]<=e[i])t[i][j]=d[i][j]/s[i];
				else t[i][j]=-1;
			}
		}
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)r[i][j]=t[i][j];
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				for(int k=0;k<n;k++)if(i!=k&&i!=j&&k!=j&&r[j][i]!=-1&&r[i][k]!=-1)
				{
					double mi=r[j][i]+r[i][k];
					if(r[j][k]<0||r[j][k]>mi)r[j][k]=mi;
				}
			}
		}
		/*for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)printf("%.3lf ",r[i][j]);puts("");
		}*/
		for(int i=0;i<m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			x--;y--;
			printf(" %.9lf",r[x][y]);
		}
		puts("");
	}
	return 0;
}

