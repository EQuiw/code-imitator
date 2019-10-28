#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
#define eprintf(...) fprintf(stderr,__VA_ARGS__)

const int N = 1005;

db d;
int n;

int main(){
	freopen("A-small-attempt0.in","r",stdin);
	freopen("A.out","w",stdout);
	int T; scanf("%d",&T);
	for(int Case=1;Case<=T;Case++){
		scanf("%lf%d",&d,&n);
		db t = 0;
		for(int i=1;i<=n;i++){
			db k, s; scanf("%lf%lf",&k,&s);
			t = max(t, (d - k) / s);
		}
		printf("Case #%d: %.12lf\n", Case, d / t);
	}
}
