#include<iostream>
#include<gmpxx.h>

#include "PaillierCryptoSystem.h"
using namespace std;

int main()
{
    PaillierCryptoSystem pcs(30);

    PaillierPlaintext m,m1,m2;
    PaillierCiphertext c1,c2,c3;
    m1=100;m2=101;
    c1=pcs.enc_u(m1);
    c2=pcs.enc_u(m2);
    m1=pcs.dec(c1);
    m2=pcs.dec(c2);
    c3=pcs.mul(c1,c2);
    cout<<c1<<" "<<c2<<endl;
    cout<<m1<<" "<<m2<<endl;
    cout<<c3<<endl;
    m=pcs.dec(c3);
    cout<<m<<endl;

    return 0;
}
