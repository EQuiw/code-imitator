#include <algorithm>
#include <float.h>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <vector>
using namespace std;

void convert(string &str) {
  int decreased = -1;
  for (int i = 1; i < str.size(); i++) {
    if (str[i] < str[i - 1]) {
      decreased = i;
      break;
    }
  }
  if (decreased != -1) {
    for (int i = decreased; i < str.size(); i++) {
      str[i] = '9';
    }
    str[decreased - 1]--;
    convert(str);
  }
}

int main() {
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; t++) {
    string str;
    cin >> str;
    convert(str);
    cout << "Case #" << (t + 1) << ": " << atoll(str.c_str()) << endl;
  }
}
