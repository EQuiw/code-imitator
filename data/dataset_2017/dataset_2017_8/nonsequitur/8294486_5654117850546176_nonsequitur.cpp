#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		int N, R, O, Y, G, B, V;
		cin >> N >> R >> O >> Y >> G >> B >> V;
	
		cout << "Case #" << t << ": ";

		vector<pair<int, char>> vec;
		vec.emplace_back(R, 'R');
		vec.emplace_back(Y, 'Y');
		vec.emplace_back(B, 'B');

		sort(vec.rbegin(), vec.rend());

		{
			string ans;
			for (int i = 0; i < N; i++) {
				int use;
				if (ans.empty()) use = 0;
				else {
					if (ans.back() == vec[0].second || vec[0].first == 0) {
						if (vec[1].first > vec[2].first) use = 1;
						else use = 2;
					} else {
						use = 0;
					}
				}

				if (vec[use].first <= 0) break;

				ans += vec[use].second;
				vec[use].first -= 1;
			}
			if (ans.size() != N || ans.front() == ans.back()) cout << "IMPOSSIBLE\n";
			else cout << ans << '\n';
		}
	}

	return 0;
}
