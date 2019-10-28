#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

bool cmp (int a, int b) {
  return a>=b;
}

int main() {
  int TT;
  cin>>TT;
  for (int T=1;T<=TT;++T) {
    int n;
    cin>>n;
    int a[10];
    for (int i=0; i<6; ++i) cin>>a[i];
    string ans="";
    if (a[0]>0) { ans+='R'; --a[0]; }
    else if (a[2]>0) { ans+='Y'; --a[2]; }
    else { ans+='B'; --a[4]; }
    for (int i=1; i<n; ++i) {
    //  cout<<ans<<endl;
      if (ans[i-1]=='R') {
        if (a[2]>=a[4] && a[2]>0) { ans+='Y'; --a[2]; }
        else if (a[4]>0) { ans+='B'; --a[4]; }
        else break;
      }
      else if (ans[i-1]=='Y') {
        if (a[0]>=a[4] && a[0]>0) { ans+='R'; --a[0]; }
        else if (a[4]>0) { ans+='B'; --a[4]; }
        else break;
      }
      else {
        if (a[0]>=a[2] && a[0]>0) { ans+='R'; --a[0]; }
        else if (a[2]>0) { ans+='Y'; --a[2]; }
        else break;
      }
    }
    cout<<"Case #"<<T<<": ";
    if (ans.size()==n && ans[0]!=ans[n-1]) cout<<ans<<endl;
    else cout<<"IMPOSSIBLE"<<endl;
  }
}
