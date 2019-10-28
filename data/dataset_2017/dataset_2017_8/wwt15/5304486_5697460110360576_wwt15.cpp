#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
#define eprintf(...) fprintf(stderr,__VA_ARGS__)

const int N = 55, P = 55;

int n, p;
int r[N], q[N][P];
pii t[N][P];
int pt[N];

bool cmp(const pii &a, const pii &b){if(a.second!=b.second) return a.second<b.second; return a.first<b.first;}

int main(){
	freopen("B-small-attempt0.in","r",stdin);
	freopen("B.out","w",stdout);
	int T; scanf("%d",&T);
	for(int Case=1;Case<=T;Case++){
		scanf("%d%d",&n,&p);
		for(int i=1;i<=n;i++) scanf("%d",&r[i]);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=p;j++){
				scanf("%d",&q[i][j]);
				int l, r;
				l = 0; r = int(1e6) + 5;
				while(r-l>1){
					int mid = (l+r)/2;
					if(10LL * q[i][j] >= 9LL * mid * ::r[i]) // q[i][j] / (mid * r[i]) >= 9 / 10
						l = mid;
					else
						r = mid;
				}
				t[i][j].second = l;
				l = 0; r = int(1e6) + 5;
				while(r-l>1){
					int mid = (l+r)/2;
					if(10LL * q[i][j] <= 11LL * mid * ::r[i]) // q[i][j] / (mid * r[i]) <= 11 / 10
						r = mid;
					else
						l = mid;
				}
				t[i][j].first = r;
			//	printf("(%d, %d)\n", t[i][j].first, t[i][j].second);
			}
			sort(t[i]+1,t[i]+p+1,cmp);
		}
		for(int i=1;i<=n;i++) pt[i]=1;
		bool ok = true;
		int ans = 0;
		for(int o=1;o<=int(1e6)+5;o++){
			bool flag = true;
			while(true){
				for(int i=1;i<=n;i++){
					for(;pt[i]<=p&&t[i][pt[i]].second<o;pt[i]++);
					if(pt[i]>p) {
						ok = false;
						break;
					}
					if(t[i][pt[i]].first>o)
						flag = false;
				}
				if(!ok) break;
				if(!flag) break;
				ans++;
				for(int i=1;i<=n;i++) pt[i]++;
			}
			if(!ok) break;
		}
		printf("Case #%d: %d\n", Case, ans);
	}
}
