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


char s[20];

lli solve(){
	scanf("%s",s);
	int ls=strlen(s);
	for(;;){
		bool ok = true;
		rep(i,ls-1){
			if(s[i]>s[i+1]){
				ok=false;
				s[i]-=1;
				reg(j,i+1,ls-1){
					s[j]='9';
				}
				break;
			}
		}
		if(ok)break;
	}
	
	lli res=0;
	rep(i,ls){
		res *= 10;
		res += s[i]-'0';
	}
	return res;
}

int main(void){
	int qn;
	scanf("%d",&qn);
	reg(qqq,1,qn){
		lli x = solve();
		printf("Case #%d: %lld\n",qqq,x);
	}
	return 0;
}




