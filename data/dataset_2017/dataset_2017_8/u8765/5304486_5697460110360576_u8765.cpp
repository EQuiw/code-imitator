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

typedef pair<int,int> PI;

PI factor[50][50];
int N; // ingredients
int P; // packages per ingredient

bool search( int k, int min_f, int max_f ) {
	assert( min_f <= max_f );
	
	if( k == N ) {
		return true;
	}
	
	for( int i = 0; i < P; ++i ) {
		if( factor[k][i].second == 0 ) continue;
		if( min_f > factor[k][i].second || max_f < factor[k][i].first ) continue;
		if( search( k+1, max( min_f, factor[k][i].first ), min( max_f, factor[k][i].second ) ) ) {
			factor[k][i].second = 0;
			return true;
		}
	}
	return false;
}

int main() {
	int cases;
	int target[50];
	
	cin >> cases;
	for( int caseid = 1; caseid <= cases; ++caseid ) {
		cout << "Case #" << caseid << ": ";
		cin >> N >> P;
		assert( 1 <= N && N <= 50 && 1 <= P && P <= 50 );
		for( int i = 0; i < N; ++i ) {
			cin >> target[i];
		}
		for( int i = 0; i < N; ++i ) {
			for( int j = 0; j < P; ++j ) {
				int a;
				cin >> a;
				
				int u = 1;
				int v = 100000000;
				while( u <= v ) {
					int w = (u+v)/2;
					if( 10*a >= 9LL*w*target[i] ) {
						u = w+1;
					} else {
						v = w-1;
					}
				}
				int max_f = v;
				
				
				u = 1;
				v = 100000000;
				while( u <= v ) {
					int w = (u+v)/2;
					if( 10*a <= 11LL*w*target[i] ) {
						v = w-1;
					} else {
						u = w+1;
					}
				}
				int min_f = u;
				
				//assert( min_f <= max_f );
				if( max_f < min_f ) max_f = 0;
				factor[i][j] = PI(min_f,max_f);
			}
			sort( factor[i], factor[i]+P );
		}
		int res = 0;
		for( int i = 0; i < P; ++i ) {
			if( search( 0, 0, 100000000 ) ) {
				++res;
			}
		}
		cout << res << endl;

	}
	return 0;	
}
