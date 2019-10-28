#include <bits/stdc++.h>

using namespace std;
using ll = unsigned long long;

vector<ll> guys;

void solve(int last, int left, ll x = 0) {
	if (left == 0) {
		guys.push_back(x);
		return;
	}

	for (int d = last; d < 10; d++) {
		solve(d, left - 1, x * 10 + d);
	}
}

int main() {
	ios::sync_with_stdio(false);

	int T; cin >> T;

	solve(0, 19, 0);

	for (int t = 1; t <= T; t++) {
		ll x; cin >> x;

		auto it = upper_bound(begin(guys), end(guys), x) - 1;
		cout << "Case #" << t << ": ";
		cout << *it << '\n';
	}

	return 0;
}
