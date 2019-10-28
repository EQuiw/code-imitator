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
	
	cin >> cases;
	for( int caseid = 1; caseid <= cases; ++caseid ) {
		cout << "Case #" << caseid << ": ";
		int N, R, O, Y, G, B, V;
		cin >> N >> R >> O >> Y >> G >> B >> V;
		
		pair<int,char> cnt[3] = {{R,'R'},{Y,'Y'},{B,'B'}};
		sort( cnt, cnt+3, greater<pair<int,char>>() );
		
		string res;
		
		int last = -1;
		bool ok = true;
		for( int i = 0; i < N; ++i ) {
			int cur = -1;
			for( int j = 0; j < 3; ++j ) {
				if( j != last && cnt[j].first > 0 ) {
					if( cur == -1 || cnt[j].first > cnt[cur].first ) {
						cur = j;
					}
				}
			}
			if( cur == -1 ) {
				ok = false;
				break;
			}
			--cnt[cur].first;
			res += cnt[cur].second;
			last = cur;
		}
		if( !ok || res[N-1] == res[0] ) cout << "IMPOSSIBLE\n";
		else cout << res << endl;
	}
	return 0;	
}
