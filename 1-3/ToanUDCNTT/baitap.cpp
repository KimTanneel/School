#include <iostream>
#include <math.h>
using namespace std;
 
 float solvefc(int x, int n){
    	if(n==0){
    		return 1;
		}	
		if(n%2==0){
			return pow(x,n/2.0)*pow(x,n/2.0);
		}
		if(n%2==1){
			return pow(x,n/2.0)*x;
		}
    }
int main(){
   float x =solvefc(2,3);
   cout<<x<<endl;
}

