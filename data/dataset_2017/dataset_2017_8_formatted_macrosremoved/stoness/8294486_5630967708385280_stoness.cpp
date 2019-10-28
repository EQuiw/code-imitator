//
//  main2017b.cpp
//  Codejam2015
//
//  Created by stoness on 17/4/22.
//  Copyright © 2017年 sts. All rights reserved.
//

#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <list>

using namespace std;

double p1() {
  int d, n, k(0), s(0);
  int i(0);
  double ma(0), t(0);
  cin >> d >> n;
  for (i = 0; i < n; ++i) {
    cin >> k >> s;
    t = (d - k) * 1.0 / s;
    ma = max(ma, t);
  }
  return d / ma;
}

int p2() { return 0; }

int p3() { return 0; }

int main(int argc, const char *argv[]) {
  int T(0);
  double r1(0);
  cin >> T;
  for (int i = 0; i < T; ++i) {
    r1 = p1();
    printf("Case #%d: %.8lf\n", i + 1, r1);
    // cout<<"Case #"<<i+1<<": "<<r1<<endl;//p1();
    // if (r1<0) cout<<"IMPOSSIBLE"<<endl;
    // else      cout<<r1<<endl;
  }
  return 0;
}
