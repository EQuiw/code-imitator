#include <bits/stdc++.h>
using namespace std;

ifstream fin("A-small-attempt0.in");
ofstream fout("A-small0.out");

void rsolve(int r0, int r1, int c0, int c1, vector<string> &rows) {
	vector<pair<int, int>> founds;
	for (int i = r0; i < r1; i++)
		for (int j = c0; j < c1; j++)
			if (rows[i][j] != '?') founds.push_back({i, j});
	cout << r0 << ' ' << r1 << ' ' << c0 << ' ' << c1 << ' ' << founds.size() << '\n';
	if (founds.size() == 0) {
		cout << "WTF???\n";
		return;
	}
	if (founds.size() == 1) {
		char found = rows[founds[0].first][founds[0].second];
		for (int i = r0; i < r1; i++)
			for (int j = c0; j < c1; j++)
				rows[i][j] = found;
		return;
	}
	else {
		int R1 = founds[0].first, C1 = founds[0].second, R2 = founds[1].first, C2 = founds[1].second;
		if (C1 == C2) {
			rsolve(r0, max(R1, R2), c0, c1, rows);
			rsolve(max(R1, R2), r1, c0, c1, rows);
		}
		else {
			rsolve(r0, r1, c0, max(C1, C2), rows);
			rsolve(r0, r1, max(C1, C2), c1, rows);
		}
	}
	cout << r0 << ' ' << r1 << ' ' << c0 << ' ' << c1 << "done\n";
}

void solve() {
	int r, c;
	fin >> r >> c;
	vector<string> rows(r);
	for (string &s : rows) fin >> s;
	rsolve(0, r, 0, c, rows);
	for (string s : rows) fout << s << '\n';
	cout << "solve done";
}

int main() {
	int t;
	fin >> t;
	for (int i = 0; i < t; i++) fout << "Case #" << i+1 << ":\n", solve();
}
