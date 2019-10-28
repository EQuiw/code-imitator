//============================================================================
// Name        : jam17cpp.cpp
// Author      : Javier Sardinas
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <queue>
#include <bits/stdc++.h>

using namespace std;


void p2017_1a_b_small() {
	int t;
	cin >> t;
	for (int c = 1; c <= t; ++c){

		cout << "Case# " << c << ": " << c << "\n";
	}
}

void p2017_1a_a_small() {
	int t, r, c;
	cin >> t;
	int emptyrows[25];
	char s[26][26];
	for (int cs = 1; cs <= t; ++cs){
		cin >> r >> c;
		memset(emptyrows, 0, sizeof(emptyrows));
		for (int i = 0; i < r; ++i)
			cin >> s[i];
		for (int i = 0; i < r; ++i){
			int j;
			for (j = 0; j < c && s[i][j] == '?'; ++j);
			if (j == c)emptyrows[i] = 1;
			else{
				int k;
				for(k = 0; k < j; ++k)
					s[i][k] = s[i][j];
				k = j;
				for(;j < c; ++j)
					if(s[i][j] == '?')
						s[i][j] = s[i][k];
					else
						k = j;
			}
		}
		int last = 0;
		while(emptyrows[last] == 1)last++;
		for(int i = last; i >=0; i--)
			for(int j = 0; j < c; ++j)
				s[i][j] = s[last][j];
		for(int i = last; i < r; ++i)
			if(emptyrows[i] == 1)
				for(int j = 0; j < c; ++j)
					s[i][j] = s[last][j];
			else
				last = i;

		cout << "Case #" << cs << ":\n";
		for (int i = 0; i < r; ++i)
			cout << s[i] << "\n";
	}
}

void p2017_1a_c_small() {
	int t;
	cin >> t;
	for (int c = 1; c <= t; ++c){

		cout << "Case# " << c << ": " << c << "\n";
	}
}

int main() {

	p2017_1a_a_small();

	return 0;
}
