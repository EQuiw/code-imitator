#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int tc;
lli hd,ad,hk,ak,b,d;

lli attackturns(lli num_buffs){
	if(num_buffs==0 && ad==0) return 9999999999;
	return num_buffs + (hk/(num_buffs*b+ad)) + (( hk % (num_buffs*b+ad) == 0 ) ? 0 : 1) ;
}

lli simulate(lli cur_hp,lli n_attacks_needed){
	lli count = 0;
	while(count < 10000){
		count++;
		if(cur_hp>ak || n_attacks_needed==1){
			n_attacks_needed--;
			if(n_attacks_needed==0) break;
		} else {
			cur_hp = hd;
		}
		cur_hp -= ak;
	}
	return count;
}

int main(){
	cin >> tc;
	for(int t=1;t<=tc;t++){
		cin >> hd >> ad >> hk >> ak >> b >> d;
		lli ans = 9999999999;
		lli num_attacks = 9999999999;
		if(b!=0){
			lli ub=1000000009,lb=0;
			while(ub-lb>2){
				lli m1 = (ub+lb*2)/3;
				lli a1 = attackturns(m1);
				lli m2 = (ub*2+lb)/3;
				lli a2 = attackturns(m2);
				if(a1<a2){
					ub = m2;
				} else {
					lb = m1;
				}
			}
			for(int i=lb;i<=ub;i++){
				// cout << i << ":" << attackturns(i) << " ";
				num_attacks = min(num_attacks,attackturns(i));
			}
		} else {
			num_attacks = attackturns(0);
		}
		// cout << num_attacks <<  endl;
		// simulate heals and debuffs
		lli cur_hd = hd;
		for(int i=0;i<10;i++){
			// find out how many turns needed if i only attack from hereon:
			// cout << i << "b/h needs " << simulate(cur_hd,num_attacks) << endl;
			ans = min(ans,i+simulate(cur_hd,num_attacks));
			if(cur_hd>ak-d){
				if(ak==0) break;
				ak = max(ak-d,0LL);
			} else {
				cur_hd = hd;
			}
			cur_hd = cur_hd - ak;
		}
		if(ans<10000){
			cout << "Case #" << t << ": " << ans << endl;
		} else {
			cout << "Case #" << t << ": IMPOSSIBLE\n";
		}
		
	}
}