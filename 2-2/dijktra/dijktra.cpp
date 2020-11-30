#include <iostream>
#include <fstream>	
#include <string.h>
using namespace std;
int n,minn,i;
int a[100][100],f,l;
bool b[100];
int c[100],d[100];

void readfile()
{
	string name;	
 	ifstream fi("badien.txt");
	ofstream fo("output.txt");
	fi>>n;
	fi>>f;fi>>l;
	for(i=1;i<=n;i++)
	{	
		for (int j=1;j<=n;j++){
			fi>>a[i][j];	
		}
	}
	for (i=1;i<=n;i++)
	{
		b[i]=false;
		d[i]=100000;

	}
	d[f]=0;c[f]=0;
	fi.close();
	fo.close();
}

void dijkstra()
{
	do{
		cout<<"break";
		minn=100000;
	for(i=1;i<=n;i++)
		if(b[i]=false)
			if(minn>d[i]) 
			{
				minn=d[i];
				f=i;
			}
	b[f]=true;
		if (f!=l)
		{
			for( i=1;i<=n;i++)
				if(	a[f][i]>0)
					if(d[f]+a[f][i]<d[i])
					{
						d[i]=d[f]+a[f][i];
						c[i]=f;
					}
		}	
	}
	while(b[l]=true);
	
}
int main()
{
	readfile();
	dijkstra();
//for(i=1;i<=n;i++)
//	{	
//		for (int j=1;j<=n;j++){
//			cout<<a[i][j];	
//		}
//	}
	cout<<d[i];
}
