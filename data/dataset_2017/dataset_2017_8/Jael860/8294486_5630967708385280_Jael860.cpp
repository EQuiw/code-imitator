#include <bits/stdc++.h>


#define debug(x) cerr<< #x << ": "<< x << endl;
#define print(x) cerr<< x << endl;

#define mp make_pair
#define pb push_back
#define all(x) (x).begin() , (x).end()
#define rall(x) (x).rbegin() , (x).rend()
#define REP(i,x,y) for(int i=x;i<y;i++)
#define REPIT(it,A) for(typeof(A.begin()) it = (A.begin()); it!=A.end();it++)
#define fst first
#define snd second
#define sqr(x) ((x)*(x))

#define fastio ios_base::sync_with_stdio(0);cin.tie(0);
#define ones(x) __builtin_popcountll(x)
using namespace std;

typedef pair<int,int> ii ;
typedef long long ll ;
typedef vector<int> vi;
typedef vector<ii> vii;

const int MAXN = 1200;
int n;
ll D;
ll phorse[MAXN];
double vhorse[MAXN];

bool check(double v){

    REP(i,0,n){
        if(vhorse[i] >= v ) continue;

        double x = v*phorse[i]/(v - vhorse[i]);
        if(x < D) return false;
    }
    return true;
}

int main(){
    fastio;
    int T;
    
    cin >> T;

    REP(test,1,T+1){
        cout<<"Case #"<<test<<": ";
        cin  >> D >> n;
        REP(i,0,n){
            cin >> phorse[i] >> vhorse[i] ;
        }
        double lo = 0.0;
        double hi = 1e16;
        REP(ii,0,120){
            double mid = (lo+hi) / 2.0;
            if(check(mid)){
                lo = mid;
            }else{
                hi = mid;
            }
        }
        double res = (lo+hi)/2.0;
        cout<<setprecision(12)<<fixed<<res<<endl;
    }



    return 0;
}
