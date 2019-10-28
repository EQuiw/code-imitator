#include <bits/stdc++.h>


using namespace std;
pair<long long,long long> K[1005];
double T[1005][1005];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;cin >> t;int index=1;
    while(t--){
            long long d,n;cin >> d >> n;
            for(int i=1;i<=n;++i)
                cin >> K[i].first >> K[i].second;
            double low=1e-10;
            double high=1e30;

            int coun=0;

            while(coun!=300){
                double mid=(low+high)/2.0;
                double check=((1.0*d)/mid);
                bool flag=1;
                for(int i=1;i<=n;++i){
                    if(mid<=K[i].second)
                        continue;
                    double tim=(1.0*K[i].first)/(1.0*mid-1.0*K[i].second);
                    if(tim<=check){
                        flag=0;break;
                    }
                }
                if(flag){
                    low=mid;
                }
                else
                    high=mid;
                ++coun;
            }
            cout << "Case #" << index++ << ": ";
            double ans=(low+high)/2.0;
            printf("%.10f\n",ans);
    }

    return 0;
}
