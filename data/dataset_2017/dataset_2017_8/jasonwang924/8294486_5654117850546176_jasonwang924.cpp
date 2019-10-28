#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
	int T;
	cin >> T;
	for(int z = 0; z < T; ++z) {
		int n,r,o,y,g,b,v;
		cin >> n >> r >> o >> y >> g >> b >> v;
		if(n == 2) {
			if(r>1||o>1||y>1||g>1||b>1||v>1) {
				cout << "Case #" << z+1 << ": IMPOSSIBLE" << "\n";
				continue;
			}
			if(o == 1 && b == 0) {
				cout << "Case #" << z+1 << ": IMPOSSIBLE" << "\n";
				continue;
			}
			if(g == 1 && r == 0) {
				cout << "Case #" << z+1 << ": IMPOSSIBLE" << "\n";
				continue;
			}
			if(v == 1 && y == 0) {
				cout << "Case #" << z+1 << ": IMPOSSIBLE" << "\n";
				continue;
			}
			cout << "Case #" << z+1 << ": ";
			if(r == 1) cout << 'R';
			if(o == 1) cout << 'O';
			if(y == 1) cout << 'Y';
			if(g == 1) cout << 'G';
			if(b == 1) cout << 'B';
			if(v == 1) cout << 'V';
			cout << '\n';
			continue;
		}
		if(n == 3) {
		 	if(r!=1 || y!=1 || b!=1) {
				cout << "Case #" << z+1 << ": IMPOSSIBLE" << "\n";
				continue;
			}
			else {
				cout << "Case #" << z+1 << ": RYB" << "\n";
				continue;
			}
		}
		if(o > b*2 || g > r*2 || v > y*2) {
			cout << "Case #" << z+1 << ": IMPOSSIBLE" << "\n";
			continue;
		}
		int r2 = r - g*2;
		int y2 = y - v*2;
		int b2 = b - o*2;
		vector<pair<int, char> > table;
		table.push_back(pair<int, char>(r2, 'R'));
		table.push_back(pair<int, char>(y2, 'Y'));
		table.push_back(pair<int, char>(b2, 'B'));

		sort(table.begin(), table.end());

		int total = r2+y2+b2;
		if(table[2].first*2 > total) {
			cout << "Case #" << z+1 << ": IMPOSSIBLE" << "\n";
			continue;
		}
		int remain = table[0].first+table[1].first-table[2].first;
		string res,res2;
		for(int i = 0; i < table[2].first; ++i) {
			if(i < remain) {
				res.push_back(table[2].second);
				res.push_back(table[1].second);
				res.push_back(table[0].second);
			}
			else if(i < table[1].first) {
				res.push_back(table[2].second);
				res.push_back(table[1].second);
			}
			else {
				res.push_back(table[2].second);
				res.push_back(table[0].second);
			}
		}
		for(int i = 0; i < res.size(); ++i) {
			if(res[i] == 'R') {
				if(g > 0) {
					res2.append("RGR");
					--g;
				}
				else res2.append("R");
			}
			if(res[i] == 'Y') {
				if(g > 0) {
					res2.append("YVY");
					--g;
				}
				else res2.append("Y");
			}
			if(res[i] == 'B') {
				if(g > 0) {
					res2.append("BOB");
					--g;
				}
				else res2.append("B");
			}

		}

		cout << "Case #" << z+1 << ": " << res2 << "\n";
	}
}