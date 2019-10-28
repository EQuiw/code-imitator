#include <iostream>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;
	for(int i = 0; i < T; ++i) {
		string s;
		cin >> s;
		int j = 1;
		while(s[0] == '0') {
			s.erase(s.begin());
		}
		while(j < s.size()) {
			if(s[j] < s[j-1]) {
				for(int k = j; k < s.size(); ++k) {
					s[k] = '9';
				}
				--s[j-1];
				--j;
				while(j > 0 && s[j] < s[j-1]) {
					s[j] = '9';
					--s[j-1];
					--j;
				}
				break;
			}
			++j;
		}
		while(s[0] == '0') {
			s.erase(s.begin());
		}
		cout << "Case #" << i+1 << ": " << s << "\n";
	}
}