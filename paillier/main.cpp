#include<iostream>
#include<gmpxx.h>

#include "paillier.h"
using namespace std;

int main()
{
    PaillierCiphertext pc;
    pc.set_str("123");
    cout<<pc<<endl;
    return 0;
}
