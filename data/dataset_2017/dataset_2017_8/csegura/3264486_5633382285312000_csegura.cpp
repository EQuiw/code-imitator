#include <iostream>
#include <sstream>
#include <numeric>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <float.h>
#include <strings.h>
#include <string.h>
using namespace std;

void convert(string &str){
	int decreased = -1;
	for (int i = 1; i < str.size(); i++){
		if (str[i] < str[i-1]){
			decreased = i;
			break;
		}
	}
	if (decreased != -1){
		for (int i = decreased; i < str.size(); i++){
			str[i] = '9';
		}
		str[decreased-1]--;
		convert(str);
	}
}

int main(){
	int tests;
	cin >> tests;
	for (int t = 0; t < tests; t++){
		string str;
		cin >> str;
		convert(str);
		cout << "Case #" << (t+1) << ": " << atoll(str.c_str()) << endl;
	}
}
