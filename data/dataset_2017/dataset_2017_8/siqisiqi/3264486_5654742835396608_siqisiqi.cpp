#include <cstdio>
#include <iostream>
using namespace std;
long long res1, res2 ;

void getSplit( long long n, long long &res1, long long &res2 ) {
        res1 = (n-1)/2;
        res2 = (n-1)-res1;
        if ( res1 < res2 ) swap(res1, res2);
}

void work( long long a, long long x, long long b, long long y, long long k) {
        if ( k == 0 ) {
                return ;
        }

        long long r1, r2, r3, r4;

        getSplit(x, r1, r2);
        getSplit(y, r3, r4);

        if ( k <= a ) {
                res1 = r1;
                res2 = r2;
                return ;
        }
        k -= a ;

        if ( k <= b ) {
                res1 = r3;
                res2 = r4;
                return ;
        }
        k -= b ;

        long long aa = 0 , bb = 0 ;
        long long maxr, minr ;
        maxr = max( r1, r2 ) ;
        minr = maxr - 1 ;

        if ( r1 == maxr ) aa += a ;
        else bb += a ;
        if ( r2 == maxr ) aa += a;
        else bb += a ;
        if ( r3 == maxr ) aa += b;
        else bb += b ;
        if ( r4 == maxr ) aa += b;
        else bb += b ;

        work(aa, maxr, bb , minr, k);
}

int main() {
        int T ;

        cin >> T;
        for ( int test = 1 ; test <= T ; ++ test ) {
                long long n, k;
                cin >> n >> k ;
                getSplit(n, res1, res2);
                work( 1, res1, 1, res2, k-1 );
                cout << "Case #" << test << ": " << res1 << " " << res2 << endl ;
        }

        return 0;
}
