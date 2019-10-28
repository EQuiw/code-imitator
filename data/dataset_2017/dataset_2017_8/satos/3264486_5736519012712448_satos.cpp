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



char s[1005];
int solve(){
	int k;
	scanf("%s%d",s,&k);
	int ls=strlen(s);
	rep(i,ls){
		s[i]=(s[i]=='+'?1:0);
	}
	
	int res=0;
	rep(i,ls){
		if(s[i]==0){
			if(i+k-1>=ls)return -1;
			res++;
			reg(j,i,min(ls-1,i+k-1)){
				s[j]=1-s[j];
			}
		}
	}
	return res;
}

int main(void){
	int qn;
	scanf("%d",&qn);
	reg(qqq,1,qn){
		int x = solve();
		if(x>=0)printf("Case #%d: %d\n",qqq,x);
		else printf("Case #%d: IMPOSSIBLE\n",qqq);
	}
	return 0;
}




