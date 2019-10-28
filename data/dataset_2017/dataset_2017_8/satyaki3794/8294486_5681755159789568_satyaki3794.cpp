//satyaki3794
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define MOD (1000000007LL)
#define LEFT(n) (2*(n))
#define RIGHT(n) (2*(n)+1)
 
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

ll pwr(ll base, ll p, ll mod = MOD){
ll ans = 1;while(p){if(p&1)ans=(ans*base)%mod;base=(base*base)%mod;p/=2;}return ans;
}
 

ll gcd(ll a, ll b){
    if(b == 0)  return a;
    return gcd(b, a%b);
}


const int N = 102;
int n, q;
double endurance[N], speed[N], adj[N][N], dist[N][N];

typedef pair<double, int> pdi;
void dijkstra(int src){
    for(int i=1;i<=n;i++)
        dist[src][i] = 1e15;
    priority_queue<pdi> pq;
    dist[src][src] = 0;
    pq.push(pdi(0, src));
    while(!pq.empty()){

        int v = pq.top().ss;
        double d = -pq.top().ff;
        pq.pop();
        if(d > dist[src][v])    continue;

        for(int vv=1;vv<=n;vv++){
            if(adj[v][vv] > endurance[v])   continue;
            double dd = d + adj[v][vv]/speed[v];
            if(dd < dist[src][vv]){
                dist[src][vv] = dd;
                pq.push(pdi(-dd, vv));
            }
        }
    }
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    freopen("C-small-attempt0.in", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t, x = 1;
    cin>>t;
    while(t--){

        cin>>n>>q;
        for(int i=1;i<=n;i++)
            cin>>endurance[i]>>speed[i];

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cin>>adj[i][j];
                if(adj[i][j] == -1) adj[i][j] = 1e15;
            }
        }

        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

        for(int i=1;i<=n;i++)
            dijkstra(i);

        cout<<"Case #"<<x++<<":";
        while(q--){
            int a, b;
            cin>>a>>b;
            cout<<fixed<<setprecision(7)<<" "<<dist[a][b];
        }
        cout<<endl;
    }

    return 0;
}










