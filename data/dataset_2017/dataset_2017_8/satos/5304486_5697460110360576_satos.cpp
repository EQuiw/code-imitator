#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#include<climits>
#include<string>
#include<set>
#include<map>
#include<iostream>
using namespace std;
#define rep(i,n) for(int i=0;i<((int)(n));i++)
#define reg(i,a,b) for(int i=((int)(a));i<=((int)(b));i++)
#define irep(i,n) for(int i=((int)(n))-1;i>=0;i--)
#define ireg(i,a,b) for(int i=((int)(b));i>=((int)(a));i--)
typedef long long int lli;
typedef pair<int,int> mp;
#define fir first
#define sec second
#define IINF INT_MAX
#define LINF LLONG_MAX
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define pque(type) priority_queue<type,vector<type>,greater<type> >
#define memst(a,b) memset(a,b,sizeof(a))
#define iter(v,ite) for(auto ite=(v).begin();ite!=(v).end();ite++)
#define mimunum(v,x) distance((v).begin(),lower_bound((v).begin(),(v).end(),x))


int n;
int pn;
int re[55];
int dat[55][55];


typedef pair<mp,int> mmp;
int solve(){
	priority_queue<mmp> que;
	rep(i,n)rep(j,pn){
		int x=dat[i][j];
		int t=re[i];
		//printf("%d %d\n",x,t);
		int r=(x*10+11*t-1)/(11*t);
		int l=(10*x)/(9*t);
		if(l<r)continue;
		que.push(mmp(mp(r,-1),i));
		que.push(mmp(mp(l,1),i));
	}
	
	int res=0;
	int dn[55];
	memset(dn,0,sizeof(dn));
	while(!que.empty()){
		mmp pa=que.top();
		que.pop();
		int ty=pa.fir.sec,
			ni = pa.sec;
		
		dn[ni]+=ty;
		//printf("t %d ty %d i %d\n",pa.fir.fir,ty,ni);
		dn[ni]=max(dn[ni],0);
		int ng=100;
		rep(i,n){
			ng = min(ng,dn[i]);
		}
		//printf("%d %d\n",pn,ng);
		res += ng;
		rep(i,n)dn[i]-=ng;
	}
	return res;
}

int main(void){
	int qn;
	scanf("%d",&qn);
	reg(qqq,1,qn){
		scanf("%d%d",&n,&pn);
		rep(i,n)scanf("%d",&re[i]);
		rep(i,n)rep(j,pn)scanf("%d",&dat[i][j]);
		printf("Case #%d: %d\n",qqq,solve());
	}
	return 0;
}




