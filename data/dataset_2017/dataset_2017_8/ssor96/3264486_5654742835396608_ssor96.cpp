#include <iostream>
#include <map>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int q = 1; q <= t; ++q) {
		long long int n, k;
		cin >> n >> k;
		cout << "Case #" << q << ": ";
		map<long long int, long long int> ar;
		ar[-n] = 1;
		for (;;) {
			map<long long int, long long int>::iterator it = ar.begin();
			long long int cur = -it->first - 1;
			long long int cnt = it->second;
			ar.erase(it);
			long long int l = cur / 2;
			long long int r = cur - l;
			if (k <= cnt) {
				cout << r << " " << l << endl;
				break;
			}
			k -= cnt;
			if (l) ar[-l] += cnt;
			if (r) ar[-r] += cnt;
		}
	}
}