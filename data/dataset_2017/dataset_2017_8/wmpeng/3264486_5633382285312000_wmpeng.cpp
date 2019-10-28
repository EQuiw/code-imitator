#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
	freopen("B-small-attempt0.in","r",stdin);
	freopen("B.out","w",stdout);
	int t;
	cin>>t;
	for(int I=1;I<=t;I++)
	{
		string num;
		cin>>num;
		num+='9'+1;
		int p=0;
		for(int i=1;i<num.length();i++)
			if(num[i]>num[i-1])
				p=i;
			else if(num[i]<num[i-1])
				break;
		num[p]--;
		for(int i=p+1;i<num.length();i++)
			num[i]='9';
		num.resize(num.length()-1);
		int i;
		for(i=0;i<num.length();i++)
			if(num[i]!='0')
				break;
		cout<<"Case #"<<I<<": ";
		cout<<(num.c_str())+i<<endl;
	}

	return 0;
}