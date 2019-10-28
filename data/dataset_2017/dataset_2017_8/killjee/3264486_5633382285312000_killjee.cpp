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
		cout<<"Case #"<<cc<<": ";
		cc++;
		int n;
		cin>>n;
		for (int i=n ; i>=1 ; i--) {
			string s="";
			int p=i;
			while (p!=0) {
				int b=p%10;
				char c=b+'0';
				s=c+s;
				p/=10;
			}
			bool ch=0;
			for (int j=1 ; j<s.size() ; j++) {
				if(s[j]<s[j-1]) {
					ch=1;
					break;
				}
			}
			if(!ch) {
				cout<<i<<endl;
				break;
			}
		}

	}
}