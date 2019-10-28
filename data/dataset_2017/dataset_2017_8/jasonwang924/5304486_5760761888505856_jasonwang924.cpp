#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;
	for(int i = 0; i < T; ++i) {
		int R, C;
		cin >> R >> C;
		vector< vector<char> > cake;
		cake.resize(R);
		for(int j = 0; j < R; ++j) {
			string s;
			cin >> s;
			for(int k = 0; k < C; ++k) {
				cake[j].push_back(s[k]);
			}
		}
		for(int j = 0; j < R; ++j) {
			for(int k = 0; k < C; ++k) {
				if(cake[j][k] != '?') {
					for(int l = k-1; l >= 0; --l) {
						if(cake[j][l] != '?') break;
						cake[j][l] = cake[j][k];
					}
				}
			}
		}
		vector<bool> isempty;
		isempty.resize(R);
		for(int j = 0; j < R; ++j) {
			if(cake[j][C-1] == '?') {
				int k;
				bool flag = false;
				for(k = C-1; k >= 0; --k) {
					if(cake[j][k] != '?') {
						flag = true;
						break;
					}
				}
				char temp = cake[j][k];
				if(flag) {
					for(;k < C; ++k) {
						cake[j][k] = temp;
					}
					isempty[j] = false;
				}
				else {
					isempty[j] = true;
				}
			}
		}
		for(int j = 0; j < R; ++j) {
			if(!isempty[j]) {
				for(int k = j-1; k >= 0; --k) {
					if(!isempty[k]) break;
					cake[k] = cake[j];
				}
			}
		}
		if(isempty[R-1]) {
			for(int j = R-1; j >= 0; --j) {
				if(!isempty[j]) {
					for(int k = j; k < R; ++k) {
						cake[k] = cake[j];
					}
					break;
				}
			}
		}
		cout << "case #" << i+1 << ":\n";
		for(int j = 0; j < R; ++j) {
			for(int k =0; k < C; ++k) {
				cout << cake[j][k];
			}
			cout << endl;
		}

	}
}