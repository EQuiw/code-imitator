#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int T;
int N;
int S[10];
int Temp[10];
bool err;
string seq;

char alpha[6] = { 'R','O','Y','G','B','V' };
int idx[6] = { 3,4,5,0,1,2 };

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int t;
	int i, j, k;

	scanf("%d", &T);
	for (t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (i = 0; i < 6; i++)
			scanf("%d", &S[i]);

		for (k = 0; k < 6; k += 2) {
			for (i = 0; i < 6; i++) Temp[i] = S[i];
			if (Temp[k] != 0) {
				int pos = k;

				err = false;
				seq.clear();
				for (i = 0; i < N; i++) {
					if (Temp[pos] == 0) { err = true; break; }
					Temp[pos]--; seq += alpha[pos];
					if (Temp[idx[pos]] != 0) {
						Temp[idx[pos]]--; seq += alpha[idx[pos]]; i++;
						continue;
					}
					bool found = false;
					int max = 0, select = -1;
					for (j = 0; j < 6; j += 2) {
						if (pos != j && Temp[j] != 0) {
							if (max < Temp[j]) {
								max = Temp[j];
								select = j;
								found = true;
							}
						}
					}
					if (!found && i != N - 1) { err = true; break; }
					pos = select;
				}
				if (seq.front() == seq.back()) err = true;

				if (!err) break;
				else seq.clear();
			}
		}

		if(err) printf("Case #%d: IMPOSSIBLE\n", t);
		else {
			printf("Case #%d: ", t);
			cout << seq << endl;
		}
	}
	return 0;
}