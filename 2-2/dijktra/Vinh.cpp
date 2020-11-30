#include<stdio.h>
#include<math.h>

int arrIn( int n, int a[] ){
	for( int i = 0; i < n; i++){
		scanf( " %d ", &a[i] );
	}
}
int arrSort( int n, int a[] ){
	int temp;
	for( int i = 0; i < n; i++) {
		for( int j = i + 1; j < n; j++ ){
			if ( a[i] > a[j] ){
			temp = a[i];
			a[i] = a[j];
			a[j] = temp; 
			}
		}
	}
}
int arrOut(int n, int a[]){
	for( int i = 0; i < n; i++){
		printf( " %d ", a[i] );
	}
}
int main(){
	int n, a[101];
	printf("Nhap N:=");
	scanf( " %d ", &n );
	arrIn( n, a );
	arrSort( n, a );
	int out = arrOut( n, a ); 
	printf( " %d ", out );
	
}

