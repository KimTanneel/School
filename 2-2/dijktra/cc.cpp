#include<stdio.h>
#include<conio.h>
using namespace std;
void nhapmang(int a[], int &n)
{ printf("nhap so phan tu :" );
  scanf("%d",&n);
  for(int i=0;i<n;i++)
  { printf(" phan tu thu %d :",i);
    scanf("%d",&a[i]);
  }
}
int xuatmang(int a[],int n)
 {for(int i=0;i<n;i++)
   {
     printf("%d \t",a[i]);
   }
 }
void sapxeptang(int a[],int n)
{
 for(int i=0;i<n-1;i++)
  for(int j=i+1;j<n;j++)
   {
    if(a[i]<a[j])
     {
       int temp=a[i];
       a[i]=a[j];
       a[j]=temp;
     }
   }
 printf("\n mang sap xep giam la: "); 
 xuatmang(a,n);   
}
int main()
{
 int a[200],n;
 nhapmang(a,n);
 xuatmang(a,n);
 sapxeptang(a,n);
 return 0;
}
