#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#ifdef DEBUG
    #define cek(x) cout<<x
#else
    #define cek(x) if(false){}
#endif // DEBUG

#define fi first
#define se second
#define INF 1000000000
#define INFLL 1000000000000000000LL
#define EPS 1e-9
#define PI acos(-1.0)
#define pb push_back
#define TC() while(tc--)
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORN(i,n) for(int i=0;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define REPN(i,a,b) for(int i=a;i<=b;i++)
#define reset(a,b) memset(a,b,sizeof(a))
#define ALL(v) v.begin(), v.end()
#define SORT(v) sort(ALL(v))
#define SORTA(v,n) sort(v, v + n)
#define SZ(v) (int) v.size()
#define sc(x) scanf("%d",&x)

void open(){
	freopen("D:/OneDrive/Code/GCJ/A-small-attempt0.in","r",stdin);
	freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int main(void){
	open();
	int tc;
	sc(tc);
	char str[1010];
	int k;

	for(int ct = 1; ct <= tc; ct++){
		scanf("%s", str);
		sc(k);
		int ret = 0;
		int len = strlen(str);

		for(int j = 0;j<len;j++){
			if(str[j] == '-'){
				if(j + k > len){
					ret = -1;
					break;
				}
				for(int l = 0;l<k;l++){
					if(str[l + j] == '+')str[l + j] = '-';
					else str[l + j] = '+';
				}
				ret++;
				// printf("%s\n", str);
			}
		}

		printf("Case #%d: ", ct);
		
		if(ret == -1){
			printf("IMPOSSIBLE\n");
		}else{
			printf("%d\n", ret);
		}
		cerr << "Test " << ct << " done \n";
	}
    return 0;
}


