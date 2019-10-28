#include<bits/stdc++.h>

using namespace std;

// input reading
template<class T>
vector<T> takeInput(int n) {
	vector<T> v;
	T a;
	for(int i = 0; i < n; i++) { cin >> a; v.push_back(a); }
	return v;
}

int main() {
	int test;
	cin >> test;
	for (int cases = 1; cases <= test; cases++) {
		string s;
		cin >> s;
		while (true) {
			int idx = -1;
			for (int i = 1; i < s.size(); i++) {
				if (s[i] < s[i-1]) {
					idx = i - 1;
					break;
				}
			}
			if (idx == -1) break;
			s[idx]--;
			for (int i = idx + 1; i < s.size(); i++) s[i] = '9';
		}

		int idx;
		for (idx = 0; s[idx] == '0'; idx++);
		s = s.substr(idx);
		cout << "Case #" << cases << ": " << s << endl;
	}
	return 0;
}
