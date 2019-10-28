#include <bits/stdc++.h>
using namespace std;

typedef int ll;

#define int long long
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()

typedef pair<int,int>pii;
typedef pair<int,pair<int,int> > piii;

const int mod=1e9+7;

int POWER[65];
int power(int a, int b) {int ret=1;while(b) {if(b&1) ret*=a;a*=a;if(ret>=mod) ret%=mod;if(a>=mod) a%=mod;b>>=1;}return ret;}
int inv(int x) {return power(x,mod-2);}

void precompute() {
	POWER[0]=1;
	for(int i=1;i<63;i++) POWER[i]=POWER[i-1]<<1LL;
}

ll main() {
	freopen("Task.in","r",stdin);freopen("Task.out","w",stdout);
	int t,cc=1;
	cin>>t;

	while (t--) {
		int n,k;
		cin>>n>>k;

		multiset<int>st;
		st.insert(n);
		int ret1,ret2;
		for (int i=0 ; i<k ; i++) {
			multiset<int>::iterator it=st.end();
			it--;
			int b=*it;
			st.erase(it);
			int a=b/2,c=(b-1)/2;
			st.insert(a);
			st.insert(c);
			ret1=a,ret2=c;
		}
		if(ret1<ret2)
			swap(ret1,ret2);
		cout<<"Case #"<<cc<<": "<<ret1<<" "<<ret2<<endl;
		cc++;
	}
}	