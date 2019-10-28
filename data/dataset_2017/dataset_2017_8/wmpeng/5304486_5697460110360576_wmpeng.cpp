#include<iostream> 
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<algorithm>
#include<math.h>
#define eps (1e-6)
using namespace std;
int n,p;
int need[55];
int qua[55][55];

bool dfs(int deep,int l,int r)
{
	if(l>r) return false;
	if(deep==n)
		return true;
	int i;
	for(i=1;i<=p;i++)
	if(qua[deep+1][i]!=-1)
	{
		int beishu1=1.0*qua[deep+1][i]/(need[deep+1]*1.1)+1-eps;//ะก 
		int beishu2=1.0*qua[deep+1][i]/(need[deep+1]*0.9)+eps;//ด๓ 
//		if(max(beishu1,l) > min(beishu2,r))
//			break;
		if(dfs(deep+1,max(beishu1,l),min(beishu2,r)))
		{
			qua[deep+1][i]=-1;
			return true;
		}
	}
	//qua[deep+1][0]=i;
	return false;
}

int main()
{
	freopen("B-small-attempt0.in","r",stdin);
	freopen("B-small-attempt0.out","w",stdout);
	int t;
	cin>>t;
	for(int I=1;I<=t;I++)
	{
		memset(need,0,sizeof(need));
		memset(qua,0,sizeof(qua));
		int ans=0;
		cin>>n>>p;
		for(int i=1;i<=n;i++)
			cin>>need[i];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=p;j++)
				cin>>qua[i][j];
		for(int i=1;i<=n;i++)
			qua[i][0]=1;
		for(int i=1;i<=n;i++)
			sort(&qua[i][1],&qua[i][p]+1);
		
		for(int i=1;i<=p;i++)
		{
			int beishu1=1.0*qua[1][i]/(need[1]*1.1)+1-eps;
			int beishu2=1.0*qua[1][i]/(need[1]*0.9)+eps;
			//cout<<"beishu: "<<beishu1<<" "<<beishu2<<endl;
			if(dfs(1,beishu1,beishu2))
				ans++;
		}
		cout<<"Case #"<<I<<": "<<ans<<endl;
	}
	
	return 0;
}
