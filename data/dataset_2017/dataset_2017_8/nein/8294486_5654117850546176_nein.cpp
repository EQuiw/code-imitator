#include<bits/stdc++.h>



int main() {
	int tc;
	scanf("%d", &tc);
	int P = 0;
	while (tc--) {
		int n, r, o, y, g, b, v;
		scanf("%d%d%d%d%d%d%d", &n, &r, &o, &y, &g, &b, &v);
		bool flag = false;
		if (r+1 < g || y+1 < v || b+1 < o) {
			
			flag = true;
			if (r >= g && y == 0 && b == 0) {
				flag = false;
			}
			if (y >= v && r == 0 && b == 0) {
				flag = false;
			}
			if (b >= o && r == 0 && y == 0) {
				flag = false;
			}
		}
		r -= g;
		y -= v;
		b -= o;

		std::vector<char> ch;
		if (r > y + b || y > r + b || b > r + y) {
			flag = true;
		}
		else {
			if (r >= y && r >= b) {
				for (int i = 0; i < r; i++) {
					ch.push_back('R');
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] == ch[(i + 1) % ch.size()]) {
						if (y != 0) {
							ch.insert(ch.begin() + i + 1, 'Y');
							y--;
						}
						else {
							ch.insert(ch.begin() + i + 1, 'B');
							b--;
						}
					}
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] != 'Y' && ch[(i + 1) % ch.size()] != 'Y' && y!=0) {
						ch.insert(ch.begin() + i + 1, 'Y');
						y--;
					}
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] != 'B' && ch[(i + 1) % ch.size()] != 'B' && b != 0) {
						ch.insert(ch.begin() + i + 1, 'B');
						b--;
					}
				}
			}
			else if (y >= r && y >= b) {
				for (int i = 0; i < y; i++) {
					ch.push_back('Y');
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] == ch[(i + 1) % ch.size()]) {
						if (r != 0) {
							ch.insert(ch.begin() + i + 1, 'R');
							r--;
						}
						else {
							ch.insert(ch.begin() + i + 1, 'B');
							b--;
						}
					}
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] != 'R' && ch[(i + 1) % ch.size()] != 'R' && r != 0) {
						ch.insert(ch.begin() + i + 1, 'R');
						r--;
					}
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] != 'B' && ch[(i + 1) % ch.size()] != 'B' && b != 0) {
						ch.insert(ch.begin() + i + 1, 'B');
						b--;
					}
				}
			}
			else {
				for (int i = 0; i < b; i++) {
					ch.push_back('B');
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] == ch[(i + 1) % ch.size()]) {
						if (y != 0) {
							ch.insert(ch.begin() + i + 1, 'Y');
							y--;
						}
						else {
							ch.insert(ch.begin() + i + 1, 'R');
							r--;
						}
					}
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] != 'Y' && ch[(i + 1) % ch.size()] != 'Y' && y != 0) {
						ch.insert(ch.begin() + i + 1, 'Y');
						y--;
					}
				}
				for (int i = 0; i < ch.size(); i++) {
					if (ch[i] != 'R' && ch[(i + 1) % ch.size()] != 'R' && r != 0) {
						ch.insert(ch.begin() + i + 1, 'R');
						r--;
					}
				}
			}
		}
		if (g != 0) {
			if (ch.empty()) {
				ch.insert(ch.begin(), 'R');
				ch.insert(ch.begin() + 1, 'G');
				g--;
			}
			for (int i = 0; i < ch.size(); i++) {
				while (ch[i] == 'R' && g!=0) {
					ch.insert(ch.begin() + i + 1, 'R');
					ch.insert(ch.begin() + i + 1, 'G');
					g--;
				}
			}
		}
		if (v != 0) {
			if (ch.empty()) {
				ch.insert(ch.begin(), 'Y');
				ch.insert(ch.begin() + 1, 'V');
				v--;
			}
			for (int i = 0; i < ch.size(); i++) {
				while (ch[i] == 'Y' && v != 0) {
					ch.insert(ch.begin() + i + 1, 'Y');
					ch.insert(ch.begin() + i + 1, 'V');
					v--;
				}
			}
		}
		if (o != 0) {
			if (ch.empty()) {
				ch.insert(ch.begin(), 'B');
				ch.insert(ch.begin() + 1, 'O');
				o--;
			}
			for (int i = 0; i < ch.size(); i++) {
				while (ch[i] == 'B' && o != 0) {
					ch.insert(ch.begin() + i + 1, 'B');
					ch.insert(ch.begin() + i + 1, 'O');
					o--;
				}
			}
		}
	

		P++;
		printf("Case #%d: ", P);
		if (flag) {
			printf("IMPOSSIBLE\n");
		}
		else {
			for (char c : ch) {
				printf("%c", c);
			}
			printf("\n");
		}

	}
}