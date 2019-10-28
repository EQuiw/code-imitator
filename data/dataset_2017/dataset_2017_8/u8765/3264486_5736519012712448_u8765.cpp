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

int main() {
	int cases;
	
	cin >> cases;
	for( int caseid = 1; caseid <= cases; ++caseid ) {
		cout << "Case #" << caseid << ": ";
		
		string s;
		int K;
		cin >> s >> K;
		bool possible = true;
		int cnt = 0;
		
		for( int i = 0; i < (int)s.size(); ++i ) {
			if( s[i] == '-' ) {
				++cnt;
				if( i+K > (int)s.size() ) {
					possible = false;
					break;
				}
				for( int j = 0; j < K; ++j ) {
					s[i+j] = (s[i+j] == '-' ? '+' : '-');
				}
			}
		}
		if( !possible ) {
			cout << "IMPOSSIBLE\n";
		} else {
			cout << cnt << endl;
		}
	}
	return 0;	
}
