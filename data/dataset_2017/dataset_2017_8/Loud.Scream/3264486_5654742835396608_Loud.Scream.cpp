#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		int n, k;
		cin >> n >> k;
		vector<bool> used(n + 5, 0);
		int ind = 1, ls = -1, rs = -1;
		used[0] = used[n + 1] = 1;
		for (int c = 1; c <= k; ++c) {
			ls = -1, rs = -1;
			for (int i = 1; i <= n; ++i) {
				if (used[i])
					continue;
				int l = i - 1, r = i + 1;
				while (l > 0 && used[l] == 0)
					--l;
				while (r <= n && used[r] == 0)
					++r;
				l = abs(l - i) - used[l];
				r = abs(r - i) - used[r];
				if (l > r)
					swap(l, r);
				if (l > ls) {
					ind = i;
					ls = l;
					rs = r;
				} else {
					if (l == ls && r > rs) {
						rs = r;
						ind = i;
					}
				}
			}
			used[ind] = 1;
		}
		cout << rs << " " << ls << "\n";
	}
	return 0;
}