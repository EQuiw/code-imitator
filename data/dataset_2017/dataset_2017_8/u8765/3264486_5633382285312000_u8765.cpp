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
		long long x;
		cin >> x;
		
		auto s = to_string(x);
		
		int invalid_index = -1;
		for( int i = 0; i < (int)s.size()-1; ++i ) {
			if( s[i] > s[i+1] ) {
				invalid_index = i;
				break;
			}
		}
		
		if( invalid_index == -1 ) {
			cout << s << endl;
			continue;
		}
		
		while( invalid_index >= 1 && s[invalid_index-1] == s[invalid_index] ) {
			--invalid_index;
		}
		
		--s[invalid_index];
		for( int i = invalid_index+1; i < (int)s.size(); ++i ) {
			s[i] = '9';
		}
		
		if( invalid_index == 0 && s[0] == '0' ) {
			s = s.substr(1);
		}
		
		cout << s << endl;
	}
	return 0;	
}
