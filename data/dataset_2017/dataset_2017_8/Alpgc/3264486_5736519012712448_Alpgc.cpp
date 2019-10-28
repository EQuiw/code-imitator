#include <bits/stdc++.h>
#define fr(a,b,c) for(int a=b;a<c;a++)
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef long long ll;
int bit[1005];
void upd(int x,int v){
	while(x<1001){
		bit[x]+=v;
		x+=x&-x;
	}
}
int qry(int x){
	int ret=0;
	while(x){
		ret+=bit[x];
		x-=x&-x;
	}
	return ret;
}
string s;
int main(){
	
	int n,m;
	cin>>n;
	fr(j,0,n){
		int k,c=0;
		cin>>s>>k;
		memset(bit,0,sizeof bit);
		fr(i,0,s.size()-k+1){
			if((s[i]!='+')^(qry(i+1)%2)){
				c++;
				upd(i+1,1);
				upd(i+k+1,-1);
			}
		}
		fr(i,s.size()-k+1,s.size()){
			if((s[i]!='+')^(qry(i+1)%2)){
				c=-1;
			}
		}
		printf("Case #%d: ",j+1);
		if(c>-1)printf("%d\n",c);
		else puts("IMPOSSIBLE");
	}
}
