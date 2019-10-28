#include <iostream>
#include <string>

using namespace std;

int T, K;
string S;

void flip(int start, int length) {
	for(int j = 0; j < length; j++) {
		S[start + j] = (S[start + j] == '-' ? '+' : '-');
	}
}

int main() {
	cin >> T;
	for(int t = 1; t <= T; t++) {
		cin >> S >> K;
		int flips = 0;
		for(int i = 0; i <= S.length() - K; i++) {
			if(S[i] == '-') {
				flip(i, K);
				flips++;
			}
		}
		bool possible = true;
		for(int i = S.length() - K + 1; i < S.length() && possible; i++) {
			if(S[i] == '-') {
				possible = false;
			}
		}
		if(possible) {
			cout << "Case #" << t << ": " << flips << endl;
		} else {
			cout << "Case #" << t << ": IMPOSSIBLE" << endl;
		}
	}
	return 0;
}