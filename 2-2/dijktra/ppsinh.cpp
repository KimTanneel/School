#include <iostream>
using namespace std;
int ktra(int a[],int l)
int main(){
	int a[100];
	int n=4                                                                                          ;
	for (int i=1;i<=n;i++)
	{
		
		a[i]=1;
		cout<<a[i]<<" ";
	}
	cout<<endl;
	int i;
		i=n;
	while (i>=1)
//	for(int i=n;i>=1;i--)
	{	
		if(a[i]<=n)
		{
			a[i]++;
			for(int j=i+1;j<=n;j++)
			{	
			a[j]=1;
			}
			i=n+1;
			for(int k=1;k<=n;k++)
			cout<<a[k]<<" ";
			cout<<endl;
			
		} 
		i--;	
	}	
}
