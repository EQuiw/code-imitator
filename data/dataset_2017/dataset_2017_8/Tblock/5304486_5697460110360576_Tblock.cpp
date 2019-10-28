#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#define EPS 1e-9

using namespace std;

typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<int> vi;
typedef vector<vi> vvi;

vi r;

bool is_valid(int i0) {
	double lbn = 9.0 / 10.0 * i0 / r[0];
	double ubn = 10.0 / 9.0 * i0 / r[0];

	if (ceil(lbn - EPS) > floor(ubn + EPS))
		return false;

	return true;
}


bool is_valid(int i0, int i1) {
	double lbn = 9.0 / 10.0 * i0 / r[0];
	double ubn = 10.0 / 9.0 * i0 / r[0];

	for (int n = ceil(lbn - EPS); n < (ubn + EPS); n++) {
		// check if ingredient 2 is within tolerance
		if (i1 > (9.0 / 10.0 * n * r[1] - EPS) && i1 < (10.0 / 9.0 * n * r[1] + EPS)) {
			return true;
		}
	}

	return false;
}

int main() {

	int t; cin >> t;
	int cas = 1;
	while (t--) {
		cout << "Case #" << cas << ": ";
		cas++;
		
		int n, p; cin >> n >> p;
		r = vi();
		for (int i = 0; i < n; i++) {
			int temp; cin >> temp;
			r.push_back(temp);
		}

		vvi q;
		for (int i = 0; i < n; i++) {
			q.push_back(vi());
			for (int j = 0; j < p; j++) {
				int temp; cin >> temp;
				q[i].push_back(temp);
			}
		}

		if (n == 1) {
			int count = 0;
			for (int i = 0; i < p; i++) {
				if (is_valid(q[0][i])) {
					count++;
				}
			}
			cout << count << endl;
		}
		else if (n == 2) {
			vi ordering = q[1];
			sort(ordering.begin(), ordering.end());
			int max_count = -1;
			int count = 0;
			do {
				count = 0;
				for (int i = 0; i < p; i++) {
					if (is_valid(q[0][i], ordering[i])) {
						count++;
					}
				}

				if (count > max_count) {
					max_count = count;
				}
			} while (next_permutation(ordering.begin(), ordering.end()));

			cout << count << endl;
		}

	}

	return 0;
}