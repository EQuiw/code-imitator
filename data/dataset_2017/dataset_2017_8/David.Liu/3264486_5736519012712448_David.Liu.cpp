#include <iostream>
#include <string>
using namespace std;

int main() {
  int T;
  cin>>T;
  for (int TT=1; TT<=T; ++TT) {
    string s;
    int k;
    cin>>s>>k;
    int l=s.length();
    int cnt=0;
    for (int i=0; i+k-1<l; ++i)
      if (s[i]=='-') {
        ++cnt;
        for (int j=i; j<i+k; ++j)
           s[j]='+'+'-'-s[j];
  //      cout<<i<<endl<<s<<endl;
      }
    cout<<"Case #"<<TT<<": ";
    bool f=1;
    for (int j=0; j<l; ++j)
      if (s[j]=='-') { f=0; break; }
    if (f) cout<<cnt<<endl; else cout<<"IMPOSSIBLE"<<endl;
  }
}
