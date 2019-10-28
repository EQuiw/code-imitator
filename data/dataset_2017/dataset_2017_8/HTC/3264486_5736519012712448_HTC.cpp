#include<iostream>
#include<cstdio>
using namespace std;
int main (){
    freopen("A-small-attempt0.in","r",stdin);
    freopen("ASOut.txt","w",stdout);
    int T;
    cin >> T;
    int N,K;
    string str;
    for(int ca=1;ca<=T;ca++){
        cin >> str >> K;
        int flag = 1,ans = 0;
        for(int i=0;i+K-1<str.length();i++){

            if(str[i] == '-'){
                for(int j=i;j<i+K;j++){
                    if(str[j] == '-')str[j] = '+';
                    else str[j] = '-';
                }
                ans++;
            }

        }
        for(int i=0;i<str.length();i++){
            if(str[i] == '-')flag = 0;
        }
        cout << "Case #" << ca << ": ";
        if(flag == 0)
            cout << "IMPOSSIBLE\n";
        else
            cout << ans <<"\n";
    }
    return 0;
}
