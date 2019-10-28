#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define dbg(x)  cout<<#x<<"="<<x<<endl
#define N 2001025
#define MOD  786433
#define pb push_back
#define iosbase  ios_base::sync_with_stdio(false)
#define dbg(x)  cout<<#x<<"="<<x<<endl


struct node{

	int l,r,len;

	bool operator <(const node &other)const{
		if(len!=other.len)
			return len>other.len;
		return l<other.l;
	}
};

set <node >s;


int main(){

	int tc;
	cin>>tc;
	ll n,k,ans1,ans2,cur;
	node temp;
	for(int ca=1;ca<=tc;ca++){
		
		cin>>n>>k;
		k--;
		temp.l=1;
		temp.r=n;
		temp.len=(temp.r-temp.l+1);
		s.insert(temp);

		while(k--){
			node temp=*s.begin();
			s.erase(s.begin());
			cur=(temp.l+temp.r)/2;

			node lef;
			lef.l=temp.l;
			lef.r=cur-1;
			lef.len=(lef.r-lef.l+1);
			node rg;
			rg.l=cur+1;
			rg.r=temp.r;
			rg.len=(rg.r-rg.l+1);
			if(lef.len>0)
				s.insert(lef);
			if(rg.len>0)
				s.insert(rg);

		}
		node temp=*s.begin();
		cur=(temp.l+temp.r)/2;
		ans1=min(cur-temp.l,temp.r-cur);
		ans2=max(cur-temp.l,temp.r-cur);
		printf("Case #%d: %lld %lld\n",ca,ans2,ans1);
		s.clear();
		

	}
}