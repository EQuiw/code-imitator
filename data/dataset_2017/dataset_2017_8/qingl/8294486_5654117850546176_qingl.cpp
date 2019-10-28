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
const int N = 1050;
typedef pair<int,int> per;
#define mp(x,y) make_pair(x,y)
int n,r,o,y,g,b,v,f,nn;
int ret[N];
per a[3];
map<ll,int>lzs;
bool gao()
{
	if(g&&r<=g)return false;
	r-=g;
	if(v&&y<=v)return false;
	y-=v;
	if(o&&b<=o)return false;
	b-=o;
	return true;
}
int main()
{
	freopen("B-small-attempt1.in","r",stdin);
	freopen("out.txt","w",stdout);
	int T,ca=1;
	scanf("%d",&T);
	while(T--)
	{
		lzs.clear();
		printf("Case #%d: ",ca++);
		scanf("%d%d%d%d%d%d%d",&n,&r,&o,&y,&g,&b,&v);
		if(o==b&&o+b==n)
		{
			for(int i=0;i<n;i++)
			{
				if(i%2)putchar('O');else putchar('B');
			}
			puts("");
			continue;
		}
		if(g==r&&g+r==n)
		{
			for(int i=0;i<n;i++)
			{
				if(i%2)putchar('G');else putchar('R');
			}
			puts("");
			continue;
		}
		if(v==y&&v+y==n)
		{
			for(int i=0;i<n;i++)
			{
				if(i%2)putchar('V');else putchar('Y');
			}
			puts("");
			continue;
		}
		if(!gao()){puts("IMPOSSIBLE");continue;}
		if(r>y+b||y>r+b||b>r+y){puts("IMPOSSIBLE");continue;}
		f=0;
		int k=0;
		nn=r+y+b;
		a[0]=mp(r,1);
		a[1]=mp(y,2);
		a[2]=mp(b,3);
		sort(a,a+3);
		int kk=a[0].first-(a[2].first-a[1].first);
		for(int i=0;i<a[1].first;i++)
		{
			ret[k++]=a[2].second;
			if(kk){ret[k++]=a[0].second;kk--;}
			ret[k++]=a[1].second;			
		}
		a[2].first-=a[1].first;
		if(a[0].first<a[2].first){puts("IMPOSSIBLE");continue;}
		for(int i=0;i<a[2].first;i++)
		{
			ret[k++]=a[2].second;
			ret[k++]=a[0].second;			
		}
		for(int i=0;i<nn;i++)
			{
				if(ret[i]==1)
				{
					if(g)
					{
						for(int j=0;j<g;j++)printf("RG");
						putchar('R');
						g=0;
					}
					else putchar('R');
				}
				else if(ret[i]==2)
				{
					if(v)
					{
						for(int j=0;j<g;j++)printf("YV");
						putchar('Y');
						v=0;
					}
					else putchar('Y');
				}
				else
				{
					if(o)
					{
						for(int j=0;j<g;j++)printf("BO");
						putchar('B');
						o=0;
					}
					else putchar('B');
				}
			}
			puts("");
	}
	return 0;
}

