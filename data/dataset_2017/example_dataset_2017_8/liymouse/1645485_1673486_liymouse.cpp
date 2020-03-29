#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <cstring>

typedef long long i64d;

using namespace std;

double p[200000];

int main()
{
	freopen("A-small-attempt1.in" , "r" , stdin);
	//freopen("input.txt" , "r" , stdin);
	freopen("A-small-attempt1.out" , "w" , stdout);
	int cas;
	scanf("%d" , &cas);
	for (int ca = 1; ca <= cas; ca ++)
	{
		printf("Case #%d: " , ca);
		int a , b;
		scanf("%d %d" , &a , &b);
		for (int i = 0; i < a; i ++) scanf("%lf" , &p[i]);
		double w1 , w2 , w3;
		//w1
		double pr = 1;
		for (int i = 0; i < a; i ++) pr *= p[i];
		w1 = (b-a+1)*pr + (b-a+1+b+1)*(1-pr);
		//w3
		w3 = min(w1 , (double)b + 2);
		//w2
		pr = 1;
		w2 = a + b + 1;
		for (int i = 0; i < a-1; i ++) pr *= p[i];
		for (int k = 1; k < a; k ++)
		{
			double x = (k + b - (a - k) + 1) * pr + (k + b - (a - k) + 1 + b + 1) * (1 - pr);
			w2 = min(w2 , x);
			if (p[k] > 0) pr /= p[k];
		}
		printf("%lf\n" , min(w2 , w3));
	}
	return 0;
}