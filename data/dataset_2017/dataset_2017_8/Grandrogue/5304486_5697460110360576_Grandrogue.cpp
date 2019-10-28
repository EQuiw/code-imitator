#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

ifstream fin("B-small-attempt1.in");
ofstream fout("out.txt");

int main() {
	int tests;
	fin >> tests;
	for (int test = 0; test < tests; ++test) {
		int ans = 0;
		int n, p;
		double x[2];
		fin >> n >> p;
		for (int i = 0; i < n; ++i) {
			fin >> x[i];
		}
		if (n == 1) {
			double y;
			for (int i = 0; i < p; ++i) {
				fin >> y;
				double k = floor(y / x[0]); 
				if ((y / (k * x[0]) >= 0.89999999995 && y / (k * x[0]) <= 1.10000000005) || (y / (k * x[0] + x[0]) >= 0.89999999995 && y / (k * x[0] + x[0]) <= 1.10000000005)){
					++ans;
				}
			}
		} else {
			double y1[8], y2[8];
			for (int i = 0; i < p; ++i) {
				fin >> y1[i];
			}
			for (int i = 0; i < p; ++i) {
				fin >> y2[i];
			}
			sort(y2, y2 + p);

			do {
				int curans = 0;
				for (int i = 0; i < p; ++i) {
					double a = y1[i], b = y2[i];
					double l1 = floor(a / x[0]);
					double l2 = floor(b / x[1]);
					if (l2 < l1) {
						swap(a, b);
						swap(l1, l2);
					}
					double s = l1 - 1000.0;
					while (s <= l2 + 1000.0) {
						if (a / (s * x[0]) >= 0.89999999995 && a / (s * x[0]) <= 1.10000000005 && b / (s * x[1]) >= 0.89999999995 && b / (s * x[1]) <= 1.10000000005) {
							curans++;
							break;
						}
						s += 1.0;
					}
				}
				if (curans > ans) {
					ans = curans;
				}
			} while (next_permutation(y2, y2+p));
		}
		fout << "Case #" << test + 1 << ": " << ans << endl;
	}
	return 0;
}