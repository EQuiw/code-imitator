#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int get_worng_pos(string num) {
	int pos = -1;
	for (auto i = num.begin(); i != num.end(); ) {
		++pos;
		auto c = *i;
		++i;
		if (c > *i && i != num.end()) {
			return pos;
		}
	}
	return -1;
}

int main() {
	int case_num;
	cin>>case_num;
	for (int case_it = 0; case_it < case_num; ) {
		++case_it;
		string st;
		cin>>st;
		stringstream ss;
		long long ans;
		int pos = get_worng_pos(st);
		while (pos != -1) {
			st[pos] = st[pos]-1;
			for (auto i = pos + 1; i < st.length(); ++i) {
				st[i] = '9';
			}
			pos = get_worng_pos(st);
		}
		ss << st;
		ss >> ans;
		cout<<"Case #"<<case_it<<": "<<ans<<endl;
	}

}