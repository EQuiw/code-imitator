#include<bits/stdc++.h>
using namespace std;
const int maxn=1111;
int dp[maxn][maxn];
char s[maxn];
int n,k;
void solve(){
	scanf("%s",s+1);
	n=strlen(s+1);
	scanf("%d",&k);

	int ans=0;
	for(int i=1;i+k-1<=n;i++){
		if(s[i]=='-'){
			ans++;
			for(int j=i;j<=i+k-1;j++){
				if(s[j]=='-')s[j]='+';
				else s[j]='-';
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(s[i]=='-'){
			puts("IMPOSSIBLE");
			return ;
		}
	printf("%d\n",ans);
}

int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: ",t);	
		solve();
	}
	return 0;
}
