#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

void mf(){
	freopen("Asmall.in","r",stdin);
	freopen("Asmall.ou","w",stdout);
}
int n,k;
string st;
void solve(){
	cin>>st>>k;
	n = st.length();
	int res = 0;
	for(int i = 0; i < n - k + 1; i++){
		if(st[i]=='-'){
			res++;
			for(int j = i; j<= i+k-1;j++)
				st[j] = (st[j]=='-')?'+':'-';
		}
	}
	for(int i = n-k+1; i <n;i++){
		if(st[i]=='-'){
			cout<<"IMPOSSIBLE"<<endl;
			return;
		}
	}
	cout<<res<<endl;
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