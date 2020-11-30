#include <iostream>  
using namespace std;  
class NhanVien { 
    int msnv;    
    string ten;
    int tuoi;
    public:  
       NhanVien(int m, string tn, int t) {    
            msnv = m;    
            ten = tn;    
            tuoi = t; 
       } 
       NhanVien(NhanVien &n) {
           msnv = n.msnv;
           ten = n.ten;
           tuoi = n.tuoi;
       }
       void HienThi() {    
            cout << ten << endl;
            cout << "   Ma so nhan vien: " << msnv << endl;
            cout << "   Tuoi: " << tuoi << endl;
       }    
};  
   
int main() {  
    NhanVien n1(111231, "Nguyen Van A", 25);    
    NhanVien n2(n1);
    n1.HienThi();    
    n2.HienThi();
    return 0;  
}
