//satyaki3794
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define MOD (1000000007LL)
#define LEFT(n) (2*(n))
#define RIGHT(n) (2*(n)+1)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;

ll pwr(ll base, ll p, ll mod = MOD){
ll ans = 1;while(p){if(p&1)ans=(ans*base)%mod;base=(base*base)%mod;p/=2;}return ans;
}


ll gcd(ll a, ll b){
    if(b == 0)  return a;
    return gcd(b, a%b);
} 


vector<int> arr;

 
int main(){
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    freopen("B-small-attempt0.in", "r", stdin);
    freopen("output.txt", "w", stdout);


// cout<<arr.size()<<endl;

    int t, x = 1;
    cin>>t;
// t=1;
    while(t--){

        ll val;
        cin>>val;

        ll z = val;
        arr.clear();
        while(val){
            arr.pb(val%10);
            val /= 10;
        }
        reverse(arr.begin(), arr.end());

        bool ok = true;
        for(int i=1;i<(int)arr.size();i++)
            if(arr[i] < arr[i-1])
                ok = false;
        if(ok){
            cout<<"Case #"<<x++<<": "<<z<<endl;
            continue;
        }

        int pos = 0;
        for(int i=1;i<(int)arr.size();i++){
            if(arr[i] < arr[i-1])   break;
            if(arr[i] > arr[i-1])   pos = i;
        }

        arr[pos]--;
        for(int i=pos+1;i<(int)arr.size();i++)
            arr[i] = 9;
        ll ans = 0;
        for(auto it : arr)
            ans = ans*10 + it;
        cout<<"Case #"<<x++<<": "<<ans<<endl;
    }

    return 0;
}
 








