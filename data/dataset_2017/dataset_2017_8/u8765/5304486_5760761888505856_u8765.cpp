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

string a[25];

void set_min( char c, int value, unordered_map<char,int>& m ) {
	auto iter = m.find( c );
	if( iter == m.end() ) {
		m[c] = value;
	} else {
		iter->second = min( iter->second, value );
	}
}

void set_max( char c, int value, unordered_map<char,int>& m ) {
	auto iter = m.find( c );
	if( iter == m.end() ) {
		m[c] = value;
	} else {
		iter->second = max( iter->second, value );
	}
}

int main() {
	int cases;
	unordered_map<char,int> min_row, min_col, max_row, max_col;
	
	cin >> cases;
	for( int caseid = 1; caseid <= cases; ++caseid ) {
		cout << "Case #" << caseid << ":\n";
		int R, C;
		cin >> R >> C;
		assert( 1 <= R && R <= 25 );
		
		min_row.clear();
		min_col.clear();
		max_row.clear();
		max_col.clear();
		
		set<char> letters;
		
		for( int r = 0; r < R; ++r ) {
			cin >> a[r];
			for( int c = 0; c < C; ++c ) {
				letters.insert( a[r][c] );
				set_min( a[r][c], r, min_row );
				set_min( a[r][c], c, min_col );
				set_max( a[r][c], r, max_row );
				set_max( a[r][c], c, max_col );
			}
		}
		
		for( char x : letters ) {
			for( int r = min_row[x]; r <= max_row[x]; ++r ) {
				for( int c = min_col[x]; c <= max_col[x]; ++c ) {
					a[r][c] = x;
				}
			}
		}
		
		/*
		// output
		for( int r = 0; r < R; ++r ) {
			cout << a[r] << endl;
		}
		*/
		
		for( int r = 0; r < R; ++r ) {
			for( int c = 0; c < C; ++c ) {
				if( a[r][c] == '?' ) {
					bool found = false;
					for( char x : letters ) {
						int min_r = min( min_row[x], r );
						int max_r = max( max_row[x], r );
						int min_c = min( min_col[x], c );
						int max_c = max( max_col[x], c );
						for( int r2 = min_r; r2 <= max_r; ++r2 ) {
							for( int c2 = min_c; c2 <= max_c; ++c2 ) {
								if( a[r2][c2] != '?' && a[r2][c2] != x ) {
									goto notok;
								}
							}
						}
						found = true;
						min_row[x] = min_r;
						max_row[x] = max_r;
						min_col[x] = min_c;
						max_col[x] = max_c;
						for( int r2 = min_r; r2 <= max_r; ++r2 ) {
							for( int c2 = min_c; c2 <= max_c; ++c2 ) {
								a[r2][c2] = x;
							}
						}
					notok:;
					}
					assert( found );
				}
			}
		}
		// output
		for( int r = 0; r < R; ++r ) {
			cout << a[r] << endl;
		}
	}
	return 0;	
}
