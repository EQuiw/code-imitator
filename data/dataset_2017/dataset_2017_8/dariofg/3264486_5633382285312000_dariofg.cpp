#include <iostream>

using namespace std;

int main()
{
	int T;
	cin >> T;
	for(int I=1;I<=T;I++)
	{
		cout << "Case #" << I << ": ";
		long long n;
		cin >> n;
		long long mask=1;
		while(mask*10<=n)mask*=10;
		//cout << mask << endl;
		if(n>=10 && (n/mask>(10*n/mask)%10))
			n=(n/mask)*mask-1;
		
		mask=1;
		while(mask>0)
		{
			aaa:;
			if(((n/mask)%10)<((n/(mask*10))%10))
			{
				n-=mask;
				//cout << n << endl;
				mask=1;
				goto aaa;
			}
			mask*=10;
		}
		cout << n << endl;
	}
}
