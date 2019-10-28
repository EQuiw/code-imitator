#include<bits/stdc++.h>
using namespace std;
const int maxn=55;
int n,m;
int r[55];
int q[55][55];

bool check(int j){

	double mn=1e9,mx=-1e9;
	for(int i=1;i<=n;i++){
		mx=max(mx,q[i][j]/(1.1*r[i]));
		mn=min(mn,q[i][j]/(0.9*r[i]));
	}

	for(int i=max(int(mx)-1,1);i<=mn+1;i++){
		bool ok=1;
		for(int k=1;k<=n;k++){
			if(!(9*r[k]*i<=10*q[k][j]&&10*q[k][j]<=11*r[k]*i)){
				ok=0;
				break;
			}
		}
		if(ok)return true;
	}
	return false;
}
int calc(){
	int ans=0;
	for(int j=1;j<=m;j++){
		if(check(j))
			ans++;
	}
	return ans;
}
int solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>r[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>q[i][j];
	if(n==1){
		return calc();
	}else{
		sort(q[2]+1,q[2]+1+m);
		int ans=0;
		do{
			ans=max(ans,calc());
		}while(next_permutation(q[2]+1,q[2]+1+m));
		return ans;
	}	
}

int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		cerr<<t<<endl;
		printf("Case #%d: %d\n",t,solve());
	}
	return 0;
}
