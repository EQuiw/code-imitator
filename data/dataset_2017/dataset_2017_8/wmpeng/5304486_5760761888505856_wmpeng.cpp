#include<iostream> 
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int n,m;
char cake[30][30];
int main()
{
	freopen("A-small-attempt0.in","r",stdin);
	freopen("A-small-attempt0.out","w",stdout);
	int t;
	scanf("%d",&t);
	for(int I=1;I<=t;I++)
	{
		memset(cake,0,sizeof(cake));
		scanf("%d%d",&n,&m);
		
		for(int i=0;i<n;i++)
			scanf("%s",cake[i]);
		vector<int> v;
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				if(cake[j][i]!='?')
				{
					v.push_back(i);
					break;
				}
//		cout<<"size="<<v.size()<<endl;
//		for(int i=0;i<v.size();i++)
//			cout<<v[i]<<" ";
//		cout<<endl;
		int sz=v.size();
		v.push_back(m);
		for(int i=0;i<sz;i++)
		{
			int ii,jj;
			for(ii=0;ii<n;ii++)
				if(cake[ii][v[i]]!='?')
					break;
			for(jj=ii-1;jj>=0;jj--)
				cake[jj][v[i]]=cake[jj+1][v[i]];
			for(ii=0;ii<n;ii++)
				if(cake[ii][v[i]]=='?')
					cake[ii][v[i]]=cake[ii-1][v[i]];
			for(int j=v[i]+1;j<v[i+1];j++)
				for(int ii=0;ii<n;ii++)
					cake[ii][j]=cake[ii][j-1];
		}
		for(int i=v[0]-1;i>=0;i--)
			for(int j=0;j<n;j++)
				cake[j][i]=cake[j][i+1];
		
		printf("Case #%d:\n",I);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
				printf("%c",cake[i][j]);
			printf("\n");
		}
			//printf("%s\n",cake[i]);
	}
	return 0;
}
