#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
unsigned long long k,n;
using ull=unsigned long long;
int getpow(ull x){
    int pow=0;
    for(ull i = 1 ; i <= x ; i*=2){
        pow++;
    }
    return pow;
}
int main (){
    int T;
    scanf("%d",&T);
    for(int I = 1 ; I <= T ; I ++){
        cin >> n >> k;
        int pow=getpow(k);
        ull upcnt=(1llu<<(pow-1))-1;
        ull left=n-upcnt;
        ull cnt=1llu<<(pow-1);
        ull base=left/cnt;
        ull curcnt=k-upcnt;
        ull ans=base;
        if(curcnt<=left%cnt)ans++;
        cout << "Case #" << I << ": " << (ans-1)/2+(ans-1)%2 << " " << (ans-1)/2 << endl;
    }

}
