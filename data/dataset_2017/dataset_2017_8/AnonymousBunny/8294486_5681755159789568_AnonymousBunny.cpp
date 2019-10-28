#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
const int mod= 1e9 + 7;
#define maxn 1020
#define inf 100000000000000LL
#define dist _ist
int a[maxn][maxn];

int e[maxn], s[maxn];

long long int dp[maxn][maxn];
long double dist[maxn][maxn];
long double res[maxn][maxn];
long double act[maxn][maxn];
long double en[maxn], sp[maxn];
void solve (int ind){
	int n, q;
	cin>>n>>q;
	for (int i=1; i<=n; i++) {
		cin>>e[i]>>s[i];
		en[i]= (long double) e[i];
		sp[i]= (long double) s[i];
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++) cin>>a[i][j];
	}	
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++){
			if (i!=j) {
				dp[i][j]= a[i][j];
				if (dp[i][j]==-1) dp[i][j]=inf;
			}
			else dp[i][j]= 0;
		}
	}
	for (int k=1; k<=n; k++){
		for (int i=1; i<=n; i++){
			for (int j=1; j<=n; j++){
				dp[i][j]= min(dp[i][j], dp[i][k]+dp[k][j]);
			}
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			dist[i][j]= (long double) dp[i][j];
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++){
			if (dist[i][j]>e[i]) res[i][j]= (long double) inf;
			else res[i][j]= dist[i][j]/sp[i];
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=1; j<=n; j++) act[i][j]= res[i][j];
	}
	for (int k=1; k<=n; k++){
		for (int i=1; i<=n; i++){
			for (int j=1; j<=n; j++) act[i][j]= min(act[i][j], act[i][k]+act[k][j]);
		}
	}
	cout<<"Case #"<<ind<<": ";
	for (int i=1; i<=q; i++){
		int u, v;
		cin>>u>>v;
		printf("%.6f ", (double) act[u][v]);
	}
	printf("\n");


}


int main(){
	int t;
	cin>>t;
	for (int i=1; i<=t; i++) solve(i);
	return 0;
}