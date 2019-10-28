#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

typedef long long LL;

int main() { 
	int cases;
	int speed[1000];
	int pos[1000];
	
	cin >> cases;
	for( int caseid = 1; caseid <= cases; ++caseid ) {
		cout << "Case #" << caseid << ": ";
		int D, N;
		cin >> D >> N;
		assert( 1 <= N && N <= 1000 );
		for( int i = 0; i < N; ++i ) {
			cin >> pos[i] >> speed[i];
		}
		double t = (double)(D-pos[0])/speed[0];
		for( int i = 1; i < N; ++i ) {
			t = max( t, (double)(D-pos[i])/speed[i] );
		}
		double v = D/t;
		printf( "%.20f\n", v ); 
	}
	return 0;	
}
