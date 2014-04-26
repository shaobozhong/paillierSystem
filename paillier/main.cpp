#include<iostream>
#include<gmpxx.h>

#include "PaillierCryptoSystem.h"
using namespace std;

int main()
{
    PaillierCiphertext pc1("123"),pc2("1");
    cout<<pc1*pc2<<endl;
    return 0;
}
