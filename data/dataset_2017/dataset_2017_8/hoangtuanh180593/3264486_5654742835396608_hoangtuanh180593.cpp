#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

void mf(){
	// freopen("input.in","r",stdin);

	freopen("Csmall1.in","r",stdin);
	freopen("Csmall1.ou","w",stdout);

	// freopen("Clarge.in","r",stdin);
	// freopen("Clarge.ou","w",stdout);
}
map<ll,ll> mm;
void solve(){
	ll n,k,x,lastx;
	mm.clear();
	cin>>n>>k;
	lastx = n;
	mm[n] = 1;
	while(k>0){
		map<ll,ll>::reverse_iterator it = mm.rbegin();
		ll x = it->first, y = it->second;
		mm.erase(x);
		x--; lastx = x;	
		k-=y;
		if(x%2==0){
			if(mm.find(x/2) != mm.end()){
				ll old = mm[x/2];
				mm[x/2] = old + y*2;
			}else{
				mm[x/2] = y*2;
			}
		}else{
			if(mm.find(x/2) != mm.end()){
				ll old = mm[x/2];
				mm[x/2] = old + y;	
			}else{
				mm[x/2] = y;
			}

			if(mm.find(x/2 + 1) != mm.end()){
				ll old = mm[x/2 + 1];
				mm[x/2 + 1] = old + y;
			}else{
				mm[x/2 + 1] = y;
			}
		}
	//	mz = max((int) mm.size(), mz);
	}
	cout<<((lastx + 1)/2)<<" "<<(lastx/2)<<endl;
	//cout<<mz<<endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	#ifdef tuanh
		mf();
	#endif
	int ntest;
	cin>>ntest;
	for(int nt = 1; nt <= ntest; nt++){
		cout<<"Case #"<<nt<<": ";
		solve();	
	}
	
	return 0;
}