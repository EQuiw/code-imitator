#include<bits/stdc++.h>
using namespace std;
int n,m;
char mp[55][55];

void fill_col(char *s){
	for(int i=1;i<=m;i++){
		if(s[i]!='?'){
			for(int j=i-1;j>=1;j--){
				if(s[j]=='?')
					s[j]=s[i];
				else break;
			}
		}
	}
	for(int i=m;i>=1;i--){
		if(s[i]!='?'){
			for(int j=i+1;j<=m;j++)
				s[j]=s[i];
			break;
		}
	}
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	for(int i=1;i<=n;i++)
		fill_col(mp[i]);
	int T=10;
	while(T--){
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='?'){
				mp[i][j]=mp[i-1][j];
			}
		}
	}
	for(int i=n-1;i>=1;i--){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='?'){
				mp[i][j]=mp[i+1][j];
			}
		}
	}
	}
	for(int i=1;i<=n;i++)
		puts(mp[i]+1);
}

int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d:\n",t);
		solve();
	}
	return 0;
}
