#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
using namespace std;

struct Horse {
	int K, S;
}horse[1000];

int cmp(const void* a, const void* b) {
	return (*(Horse*)b).K - (*(Horse*)a).K;
}

int main() {
	cout.precision(6);
	cout.flags(ios::fixed);
	int T, D, N;
	cin >> T;
	for (int c = 1; c <= T; ++c) {
		cin >> D >> N;
		double reach = 0;
		for (int i = 0; i < N; ++i) {
			cin >> horse[i].K >> horse[i].S;
			if ((D - horse[i].K) * 1.0 / horse[i].S > reach) {
				reach = (D - horse[i].K) * 1.0 / horse[i].S;
			}
		}
		//qsort(horse, N, sizeof(horse[0]), cmp);
		cout << "Case #" << c << ": " << D / reach << endl;
	}
	return 0;
}