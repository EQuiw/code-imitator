#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define re(i,a,b) for(int i = a; i <= b; i++)
#define rep(i,a,b) for(int i = a; i >= b; i--)
#define ll long long
#define MAX 20000000000000
using namespace std;
int T;
int N,Q;
double e[1010],s[1010];
double dist[1010],tmp;
double f[1010],cnt;
int main(){
//	freopen("C.in","r",stdin);freopen("C.out","w",stdout);
	scanf("%d", &T);
	re(casen,1,T)
	{
		scanf("%d%d", &N, &Q);
		re(i,0,N-1){
			scanf("%lf%lf", &e[i], &s[i]);
			f[i]=MAX;
		}
		re(i,0,N-1)
			re(j,0,N-1)
			{
				scanf("%lf", &tmp);
				if(i+1==j) dist[j] = tmp;
			}
		scanf("%lf", &tmp);
		scanf("%lf", &tmp);
		dist[0] = 0;
		f[0] = 0;
		re(i,0,N-2){
			cnt = 0;
			re(j,i+1,N-1)
			{
				cnt+=dist[j];
				if(cnt>e[i]) break;
				if(cnt/s[i]+f[i]<f[j])
					f[j] = cnt/s[i]+f[i];
			}
		}
		printf("Case #%d: %.9lf\n", casen, f[N-1]);
	}
//	fclose(stdin);fclose(stdout);
	return 0;
}
