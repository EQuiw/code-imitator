#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int cas;
int n;

const int maxn = 1005;

int D;
int k[maxn];
int v[maxn];

int main(){
	freopen("A-small-attempt0.in","r",stdin);
	freopen("A-small-attempt0.txt","w",stdout);
	cin >> T;
	cas = 0;
	while(T--){
		cas++;
		cin >> D >> n;
		for(int i = 1;i <= n;i++){
			scanf("%d%d",k + i,v + i);
		}
		double ans = 0.0;
		for(int i = 1;i <= n;i++){
			ans = max(ans,1.0 * (D - k[i]) / v[i]);
		}
		ans = 1.0 * D / ans;
		printf("Case #%d: %.10lf\n",cas,ans);
	}
	return 0;
}
