#include <cstdio>
#include <iostream>
#include <string>
using namespace std ;

int main() {

        int T ;
        cin >> T ;
        for ( int test = 1 ; test <= T ; ++ test ) {
                int N , R , O , Y , G , B , V ;
                cin >> N >> R >> O >> Y >> G >> B >> V ;

                cout << "Case #" << test << ": " ;
                if ( R > B+Y || B > R+Y || Y > R+B ) { cout << "IMPOSSIBLE" << endl; continue; }

                string ans = "";
                if ( R ) ans += "R", --R;
                else if (B) ans += "B", --B;
                else ans += "Y", --Y;

                for ( int i = 1 ; i < N ; ++i ) {
                        if ( i != N-2 ) {
                                if ( ans[i-1] == 'R' ) {
                                        if ( Y > B ) ans += "Y", --Y;
                                        else ans += "B", --B;
                                }
                                else if ( ans[i-1] == 'Y' ) {
                                        if ( B > R ) ans += "B", --B ;
                                        else ans += "R", --R;
                                }
                                else { // 'B'
                                        if ( Y > R ) ans += "Y", --Y;
                                        else ans += "R", --R;
                                }
                        }
                        else {
                                if ( ans[0] == 'R' && R ) ans += 'R', --R ;
                                else if ( ans[0] == 'Y' && Y ) ans += 'Y', --Y ;
                                else if ( ans[0] == 'B' && B ) ans += 'B', --B ;
                                else {
                                        if ( ans[i-1] == 'R' ) {
                                                if ( Y > B ) ans += "Y", --Y;
                                                else ans += "B", --B;
                                        }
                                        else if ( ans[i-1] == 'Y' ) {
                                                if ( B > R ) ans += "B", --B ;
                                                else ans += "R", --R;
                                        }
                                        else { // 'B'
                                                if ( Y > R ) ans += "Y", --Y;
                                                else ans += "R", --R;

                                        }
                                }
                        }
                }
                cout << ans << endl ;
        }

}
