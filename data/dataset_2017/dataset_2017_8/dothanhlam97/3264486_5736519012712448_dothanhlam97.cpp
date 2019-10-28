#include <bits/stdc++.h> 

using namespace std;  

int main() 
{ 
	int q, n, k; 
	char s[10001]; 
	scanf("%d", &q);  
	for (int t = 1; t <= q; ++t) { 
		scanf("%s %d", s + 1, &k);
		n = strlen(s + 1);  
		int slip = 0; 
		for (int i = 1; i <= n - k + 1; ++i) 
			if (s[i] == '-') { 
				slip ++; 
				for (int j = i , cnt = 1 ; cnt <= k && j <= n ; cnt ++, j++) { 
					if (s[j] == '-') 
						s[j] = '+'; 
					else 
						s[j] = '-';
				}
			}
		bool ok = 1; 
		for (int i = n - k + 2; i <= n; ++i) 
			if (s[i] == '-') 
				ok = 0; 
		printf("Case #%d: ", t); 
		if (!ok)
			printf("IMPOSSIBLE\n");  
		else 
			printf("%d\n", slip); 
	}
}