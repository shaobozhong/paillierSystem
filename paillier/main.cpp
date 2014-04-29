#include<iostream>
#include<gmpxx.h>

#include "PaillierCryptoSystem.h"
using namespace std;

int main()
{
    //three method to get a PaillierCrytoSystem object to do our work.
    //first
    PaillierCryptoSystem pcs(30);//this is set the bits as 30 and generate other key automaticly.
    //second assgin all key

    //PaillierCryptoSystem(int bits,const mpz_class &n,const mpz_class &n_squared,
    //const mpz_class &g,const mpz_class &n_plusone,const mpz_class &lambda,const mpz_class &x);


    //for simple i surport the string as the parameters as big integers
    //PaillierCryptoSystem(int bits,const std::string &n,const std::string &n_squared,
    //const std::string &g,const std::string &n_plusone,const std::string &lambda,const std::string &x);
    //PaillierCryptoSystem pcs(30);//this is set the bits as 30 and generate other key automaticly.

    //third set p q and call completeKey funtion
    //PaillierCryptoSystem pcs;
    //pcs.setP();
    //pcs.setQ();
    //pcs.completeKey_u();  //u is represent /dev/urandom,you can see PaillierCrytoSystem.h for detail.


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
