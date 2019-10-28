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
	freopen("D:/OneDrive/Code/GCJ/A-small-attempt1.in","r",stdin);
	freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int main(void){
	open();
	int tc;
	sc(tc);

	for(int ct = 1; ct <= tc; ct++){
		int r,c;
		sc(r);sc(c);
		string str[30];
		string ret[30];
		FOR(i,r){
			cin >> str[i];
			// if(ct == 74){
			// 	cerr << str[i] << endl;
			// }
			ret[i] = str[i];
		}

		FOR(i,r){
			FOR(j,c){
				if(str[i][j] == '?')continue;
				int minx, maxx;
				minx = maxx = i;
				int miny, maxy;
				miny = maxy = j;
				while(miny > 0 && str[i][miny - 1] == '?' && ret[i][miny - 1] == '?')miny--;
				while(maxy < c - 1 && str[i][maxy + 1] == '?' && ret[i][maxy + 1] == '?')maxy++;
				while(minx > 0){
					bool valid = true;
					for(int k = miny;k<=maxy;k++){
						if(str[minx - 1][k] != '?' || ret[minx - 1][k] != '?'){
							valid = false;
							break;
						}
					}
					if(valid){
						minx--;
					}else break;
				}
				bool adabawah = false;
				for(int k = i + 1;k<r;k++){
					FOR(l,c){
						if(str[k][l] != '?'){
							adabawah = true;
							break;
						}
					}
				}
				if(!adabawah){
					maxx = r - 1;
				}
				

				for(int k = minx;k<=maxx;k++){
					for(int l = miny;l<=maxy;l++){
						ret[k][l] = str[i][j];
					}
				}
			}
		}

		printf("Case #%d: \n", ct);
		FOR(i,r){
			cout << ret[i] << "\n";
		}

		cerr << "Test " << ct << " done \n";
	}
    return 0;
}


