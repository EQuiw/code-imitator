#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main() {
	int T;
	freopen("A-small-attempt1.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &T);
	
	for(int testCase = 1; testCase <= T; testCase++) {
		int R, C;
		scanf("%d %d", &R, &C);

		char board[30][30] = { 0, };

		queue < pair<pair<int, int>, char> > q;

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf(" %c", &board[i][j]);

				if (board[i][j] != '?') {
					q.push(make_pair(make_pair(i, j), board[i][j]));
				}
			}
		}

		while (!q.empty()) {
			int y = q.front().first.first;
			int x = q.front().first.second;
			char c = q.front().second;

			q.pop();

			if (y - 1 >= 0 && board[y - 1][x] == '?') {
				board[y - 1][x] = c;
				q.push(make_pair(make_pair(y - 1, x), c));
			}

			if (y + 1 < R && board[y + 1][x] == '?') {
				board[y + 1][x] = c;
				q.push(make_pair(make_pair(y + 1, x), c));
			}
		}

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (board[i][j] == '?') {
					char c = 'A';

					int tmpJ = j;
					while (tmpJ >= 0 && board[i][tmpJ] == '?') {
						tmpJ--;
					}

					if (tmpJ == -1) {
						tmpJ = 0;
						while (tmpJ < C && board[i][tmpJ] == '?') {
							tmpJ++;
						}
					}

					c = (tmpJ < C ? board[i][tmpJ] : c);

					board[i][j] = c;
				}
			}
		}

		printf("Case #%d:\n", testCase);
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				printf("%c", board[i][j]);
			}
			printf("\n");
		}
	}

	return 0;
}