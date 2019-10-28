#include <bits/stdc++.h> 


using namespace std;  

int main() 
{
	int q;  
	char s[20]; 
	scanf("%d", &q); 
	for (int t = 1 ; t <= q ; ++t) { 
		scanf("%s", s + 1);  
		while (1) { 
			bool check = 1;  
			for (int i = 1; i < strlen( s+1) ; ++i) 
				if (s[i] > s[i + 1]) 
					check = 0;  
			if (check) 
				break;  
			for (int i = strlen(s + 1) - 1; i ; i--) { 
				if (s[i] > s[i + 1]) 
					{ 
						s[i] --;  
						for (int j = i + 1; j <= strlen(s + 1) ; ++j) 
							s[j] = '9'; 
					}
			}
		}
		long long ans = 0; 
		for (int i = 1; i <= strlen(s + 1); ++i) 
			ans = ans * 10 + (s[i] - '0'); 
		printf("Case #%d: %lld\n", t, ans); 
	}
}