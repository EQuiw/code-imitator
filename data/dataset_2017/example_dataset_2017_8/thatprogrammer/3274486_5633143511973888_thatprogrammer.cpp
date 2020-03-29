//Hi
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
long double power(long double x, int p){
    long double ans = 1;
    for(int i=0; i< p; i++){
        ans*=x;
    }
    return ans;
}
void solve(){
    int n, k;
    long double u;
    cin>>n>>k>>u;

    long double arr[50];
    long double sum = 0;
    for(int i=0; i< n; i++){cin>>arr[i]; sum+=arr[i];}
    sort(arr, arr+n);
    long double discardProduct = 1;
    if(u==0){
        for(int i=0; i< n; i++) discardProduct*=arr[i];
        cout<<discardProduct<<endl;
        return;
    }
    for(int i=n-1;i>=0; i--){
        long double av = (sum+u);
        if((i+1)*arr[i]>av) {
            discardProduct*=arr[i];
            sum-=arr[i];
        }else{
            av=av/(long double)(i+1);
            long double ans =power(av, i+1)*discardProduct;
            cout<<fixed<<setprecision(7)<<ans<<endl;
            return;
        }
    }
    
    
}
int main()
{
    ios::sync_with_stdio(false);
    freopen("test.txt","r",stdin);
    freopen("test1.txt","w",stdout);
    int t;
    cin>>t;
    for(int i=1; i<=t; i++){
        cout<<"Case #"<<i<<": ";
        solve();
    }
    
}
