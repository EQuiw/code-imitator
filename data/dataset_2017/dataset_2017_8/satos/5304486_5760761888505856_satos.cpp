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

int h,w;
char s[30][30];
void solve(){
	reg(c,'A','z'){
		if(c>'Z' && c<='a')continue;
		int u=100,d=-1,l=100,r=-1;
		rep(y,h){
			rep(x,w){
				if(s[y][x]==c){
					u=min(u,y);
					d=max(d,y);
					l=min(l,x);
					r=max(r,x);
				}
			}
		}
		
		reg(y,u,d)reg(x,l,r){
			s[y][x]=c;
		}
	}
	
	
	rep(y,h){
		int ox=-1;
		rep(x,w){
			if(s[y][x]!='?'){
				ox=x;
				break;
			}
		}
		if(ox>=0){
			rep(x,ox)s[y][x]=s[y][ox];
			char nc=s[y][ox];
			reg(x,ox,w-1){
				if(s[y][x]=='?'){
					s[y][x]=nc;
				}
				else nc=s[y][x];
			}
		}
	}
	reg(y,1,h-1){
		if(s[y][0]!='?')continue;
		if(s[y-1][0]=='?')continue;
		rep(x,w){
			s[y][x]=s[y-1][x];
		}
	}
	ireg(y,0,h-2){
		if(s[y][0]!='?')continue;
		if(s[y+1][0]=='?')continue;
		rep(x,w){
			s[y][x]=s[y+1][x];
		}
	}
}


int main(void){
	int qn;
	scanf("%d",&qn);
	reg(qqq,1,qn){
		scanf("%d%d",&h,&w);
		rep(y,h)scanf("%s",s[y]);
		solve();
		printf("Case #%d:\n",qqq);
		rep(y,h){
			puts(s[y]);
		}
	}
	return 0;
}




