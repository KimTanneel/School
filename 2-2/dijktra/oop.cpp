#include <iostream>
using namespace std;
void show( int m)
{
	cout<<m;
	cout<<m++;
	}
int main(){
	int x=1;
	const int y=1;
	show(x);
	show(y);
}
