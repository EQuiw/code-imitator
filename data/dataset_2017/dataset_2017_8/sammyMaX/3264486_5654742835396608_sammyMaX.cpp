#include <bits/stdc++.h>
using namespace std;

ifstream fin("C-small1.in");
ofstream fout("C-small1.out");

void solve() {
	int k, n;
	fin >> k >> n;
	map<int, int> ct;
	ct[k] = 1;
	for (int i = 1; i < n; i++) {
		auto p = *(ct.rbegin());
		if (p.second == 1) ct.erase(p.first);
		else ct[p.first]--;

		ct[(p.first - 1) / 2]++;
		ct[p.first - 1 - (p.first-1)/2]++;
	}
	fout << ct.rbegin()->first/2 << ' ' << (ct.rbegin()->first-1)/2 << '\n';
}

int main() {
	int t;
	fin >> t;
	for (int i = 0; i < t; i++) fout << "Case #" << i+1 << ": ", solve();
}
