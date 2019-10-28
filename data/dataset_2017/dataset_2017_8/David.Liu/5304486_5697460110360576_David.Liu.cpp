#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
  return a>=b;
}

bool notAll(int arr[], int n, int p) {
  for (int i=0; i<n; ++i)
    if (arr[i]<p) return true;
  return false;
}

int getMax(int n, int k) {
  int ans=n/k;
  while (n>=(ans+1)*k*0.9 && n<=(ans+1)*k*1.1) ++ans;
  if (n<ans*k*0.9 || n>ans*k*1.1) return 0;
  return ans;
}

int getMin(int n, int k) {
  int ans=getMax(n,k);
  if (ans>0) while (n<=(ans-1)*k*1.1 && n>=(ans-1)*k*0.9) --ans;
  if (n<ans*k*0.9 || n>ans*k*1.1) return 0;
  return ans;
}

int main() {
  int TT;
  cin>>TT;
  for (int T=1; T<=TT; ++T) {
    int r[100], q[100][100];
    int n,p;
    cin>>n>>p;
    for (int i=0; i<n; ++i) cin>>r[i];
    for (int i=0; i<n; ++i) {
      for (int j=0; j<p; ++j)
        cin>>q[i][j];
      sort(q[i], q[i]+p, cmp);
    }
    int cnt[100];
    memset(cnt, 0, sizeof(cnt));
    int ans=0;
    bool done=0;
    while (!done && notAll(cnt, n, p)) {
      int serve=99999999;
      bool canAdd=1;
      for (int i=0; i<n; ++i) {
        int m=getMax(q[i][cnt[i]], r[i]);
        while (cnt[i]<p && m==0) {
          ++cnt[i];
          m=getMax(q[i][cnt[i]], r[i]);
        }
        if (m<serve) serve=m;
      }
      for (int i=0; i<n; ++i) {
        int m1;
        while (cnt[i]<p && (serve*r[i]*0.9>q[i][cnt[i]] || serve*r[i]*1.1<q[i][cnt[i]]))
          ++cnt[i];
        if (cnt[i]==p) {
          done=1;
          break;
        }
        if (serve==0) {

          canAdd=0;
          break;
        }
      }
      if (!done && canAdd) {
        if (serve>0) ++ans;
        for (int k=0; k<n; ++k) ++cnt[k];
      }
    }
    cout<<"Case #"<<T<<": "<<ans<<endl;
  }
}
