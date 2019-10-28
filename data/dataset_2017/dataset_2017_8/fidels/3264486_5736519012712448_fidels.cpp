#include <iostream>
using namespace std;

#define MAXN 1024
#define FLIP(c) ( (c)=='+' ? '-' : '+' )

char s[MAXN];

int main() {
	int T, t, i, j, K, RES;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> s >> K;
		
		RES = 0;
		for (i=0; s[i+K-1]!='\0'; i++) if (s[i] == '-') {
			for (j=0; j<K; j++) s[i+j] = FLIP(s[i+j]);
			RES++;
		}
		
		for (i=0; s[i]!='\0'; i++) if (s[i] == '-') break;
		cout << "Case #" << t << ": ";
		if (s[i] == '-') cout << "IMPOSSIBLE" << endl;
		else cout << RES << endl;
	}

	return 0;
}
