#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream fin("B-small-attempt0.in");
ofstream fout("out.txt");

int main() {
	int tests;
	fin >> tests;
	for (int test = 0; test < tests; ++test) {
		int s, r, y, b, ss;
		fin >> s >> r >> ss >> y >> ss >> b >> ss;
		if ((r > y + b) || (y > r + b) || (b > y + r)) {
			fout << "Case #" << test + 1 << ": " << "IMPOSSIBLE" << endl;
		} else {
			string label[3];
			int x[3];
			label[0] = "R";
			label[1] = "Y";
			label[2] = "B";
			x[0] = r;
			x[1] = y;
			x[2] = b;
			if (x[0] < x[1]) {
				swap(x[0], x[1]);
				swap(label[0], label[1]);
			}
			if (x[0] < x[2]) {
				swap(x[0], x[2]);
				swap(label[0], label[2]);
			}
			vector<string> a;
			for (int i = 0; i < x[0]; ++i) {
				string s = label[0];
				a.push_back(s);
			}
			int pos = 0;;
			for (int i = 0; i < x[1]; ++i) {
				a[pos] = a[pos] + label[1];
				pos += 1;
				pos %= x[0];
			}
			for (int i = 0; i < x[2]; ++i) {
				a[pos] = a[pos] + label[2];
				pos += 1;
				pos %= x[0];
			}
			string s = "";
			for (int i = 0; i < x[0]; ++i) {
				s += a[i];
			}

			fout << "Case #" << test + 1 << ": " << s << endl;
		}
	}
	return 0;
}