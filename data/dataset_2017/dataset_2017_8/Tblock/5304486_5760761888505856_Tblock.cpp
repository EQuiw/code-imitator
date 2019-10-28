#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<char> vc;
typedef vector<vc> vvc;

int r, c;
vvc cake;

char fillfromright(int i, int j) {
	if (j == c)
		return '?'; // reached end, nothing to fill

	if (cake[i][j] != '?')
		return cake[i][j]; // already filled


	cake[i][j] = fillfromright(i, j + 1);
	return cake[i][j];
}

char fillfromleft(int i, int j) {
	if (j < 0)
		return '?';

	if (cake[i][j] != '?')
		return cake[i][j];

	cake[i][j] = fillfromleft(i, j - 1);
	return cake[i][j];
}

int main() {

	int t; cin >> t;
	int cas = 1;
	while (t--) {
		cout << "Case #" << cas << ":";
		cas++;
		cout << endl;
		cin >> r >> c;
		cake = vvc(r, vc(c, ' '));
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				char next; cin >> next;
				cake[i][j] = next;
			}
		}

		// fill rows
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				fillfromright(i, j);
			}
		}

		for (int i = 0; i < r; i++) {
			fillfromleft(i, c - 1);
		}




		for (int i = 0; i < r; i++) {
			if (cake[i][0] == '?') {
				// empty row
				// output previous row if there was one
				if (i > 0) {
					for (int j = 0; j < c; j++) {
						cout << cake[i - 1][j];
						cake[i][j] = cake[i - 1][j];
					}
					cout << endl;
				}
				else {
					// first row, so scan down until we find a full one; guaranteed to exist
					int inext = i;
					while (inext < r && cake[inext][0] == '?')
						inext++;
					if (inext == r) {
						cout << "bad input" << endl;
					}
					for (int j = 0; j < c; j++) {
						cout << cake[inext][j];
						cake[i][j] = cake[inext][j];
					}
					cout << endl;
				}

			}
			else {
				for (int j = 0; j < c; j++) {
					cout << cake[i][j];
				}
				cout << endl;
			}
		}	

	}

	return 0;
}