#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int c = 1; c <= t; ++c) {
		cout << "Case #" << c << ": ";
		int n;
		cin >> n;
		int num = n;
		vector<int> digs;
		while (num > 0) {
			digs.push_back(num % 10);
			num /= 10;
		}
		reverse(digs.begin(), digs.end());
		int last = 0;
		int i = 0;
		while (i < digs.size() && digs[i] >= last) {
			last = digs[i];
			++i;
		}
		if (i == digs.size())
			cout << n << "\n";
		else {
			--i;
			--digs[i];
			for (int j = i + 1; j < digs.size(); ++j)
				digs[j] = 9;
			reverse(digs.begin(), digs.end());
			while (digs.size() > 1 && digs.back() == 0)
				digs.pop_back();
			reverse(digs.begin(), digs.end());
			for (auto to : digs)
				cout << to;
			cout << "\n";
		}
	}
	return 0;
}