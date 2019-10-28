#include <bits/stdc++.h>

#define F first
#define S second
#define pb push_back
#define ld long double
#define ll long long
#define int long long

using namespace std;

const int MAXN = 111 ;


#define cin fin
#define cout fout
ifstream fin ("in.in") ;
ofstream fout ("out.out") ;



int d[MAXN][MAXN] ;

ld dis[MAXN][MAXN] ;

int l[MAXN] , v[MAXN] ;

int32_t main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t ;
    cin >> t ;
    cout << fixed << setprecision(6) ;
    for(int _ = 1 ; _ <= t ; _ ++ )
    {
        int n , q ;
        cin >> n >> q ;
        for(int i = 0 ; i < n ; i ++ )
            cin >> l[i] >> v[i] ;
        for(int i = 0 ; i < n ; i ++ ) for(int j = 0 ; j < n ; j ++ )
        {
            cin >> d[i][j] ;
            if(d[i][j]==-1)
                d[i][j] = 1e18 ;
            if(i==j)
                d[i][j] = 0 ;
        }
        for(int k = 0 ; k < n ; k ++ ) for(int i = 0 ; i < n ; i ++ ) for(int j = 0 ; j < n ; j ++ )
            d[i][j] = min(d[i][j],d[i][k]+d[k][j]) ;

        for(int i = 0 ; i < n ; i ++ ) for(int j = 0 ; j < n ; j ++ )
        {
            dis[i][j] = 1e18 ;
            if(d[i][j]<=l[i])dis[i][j] = (ld) d[i][j] / (ld) v[i] ;
        }
        for(int k = 0 ; k < n ; k ++ ) for(int i = 0 ; i < n ; i ++ ) for(int j = 0 ; j < n ; j ++ )
            dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]) ;

        cout << "Case #" << _ << ": " ;
        for(int i = 0 ; i < q ; i ++ )
        {
            int s , t ;
            cin >> s >> t ;
            cout << dis[s-1][t-1] << ' ' ;
        }
        cout << '\n' ;
    }
}
