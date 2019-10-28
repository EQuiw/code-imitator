#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main(){
	freopen("C-small-1-attempt2.in","r",stdin);
	freopen("C-small-1-attempt2.out","w",stdout);
	int t;
	cin>>t;
	int cas = 0;
	while(t--){
		cas++;

		ll n,k;
		cin>>n>>k;

		while(k > 1){
			// cout<<n<<" "<<k<<endl;
			if(n&1){
				n>>=1;
				k>>=1;
			}else{
				n>>=1;
				if(k&1){
					n--;
				}
				k>>=1;
			}
		}
		printf("Case #%d: ",cas);
		cout<<n/2<<" "<<(n-1)/2<<endl;
	}
	return 0;
}
