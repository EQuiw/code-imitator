//============================================================================
// Name        : jam17cpp.cpp
// Author      : Javier Sardinas
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

void p1small() {

	int t, k;
	char s[1010];
	scanf("%d", &t);
	int c = 0;
	while (t--) {
		++c;
		scanf("%s%d", s, &k);
		int n = strlen(s);
		if (k > n) {
			printf("Case #%d: IMPOSSIBLE\n", c);
			continue;
		}
		int i;
		int count = 0;
		for (i = 0; i <= n - k; ++i)
			if (s[i] == '-') {
				count++;
				for (int j = 0; j < k; ++j)
					s[i + j] = '-' + '+' - s[i + j];
			}
		bool b = 1;
		for (; i < n && b; ++i)
			if (s[i] == '-') {
				printf("Case #%d: IMPOSSIBLE\n", c);
				b = 0;
			}
		if(b)
			printf("Case #%d: %d\n", c, count);
	}
}


void p2small(){
	int t;
	char n[20];
	scanf("%d", &t);
	int c = 0;
	while(t--){
		c++;
		scanf("%s", n);
		int i = 0;
		int len = strlen(n);
		while(i < len-1 && n[i] <= n[i+1]) i++;
		if (i == len-1)
			printf("Case #%d: %s\n", c, n);
		else{
			int last = i;
			while(i >= 0 && n[i] == n[last])i--;
			i++;
			n[i]--;
			for(i++; i < len; ++i)
				n[i] = '9';
			i = 0;
			while(n[i] == '0')i++;
			printf("Case #%d: %s\n", c, n+i);
		}
	}
}

int main() {

	p2small();
	return 0;
}
