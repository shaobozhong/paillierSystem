#include<iostream>
#include<gmpxx.h>
#include<string>
#include<fstream>
#include<sstream>
#include "PaillierCryptoSystem.h"
using namespace std;


int getPubKey(const string &name,PaillierCryptoSystem &pcs)
{
  ifstream fin("../../key/pub_key.txt");
  string str;
  while(getline(fin,str))
  {
    string keyName,n,g;
    istringstream stream(str);
    stream>>keyName>>n>>g;
    if (keyName==name)
    {
      //cout<<n<<g<<endl;
      pcs.setN(n);
      pcs.setG(g);
      fin.close();
      return 0;
    }
  }
  fin.close();
  return 1;
}


int getPriKey(const string &name,PaillierCryptoSystem &pcs)
{
  ifstream fin("../../key/pri_key.txt");
  string str;
  while(getline(fin,str))
  {
    string keyName,l,x;
    istringstream stream(str);
    stream>>keyName>>l>>x;
    if (keyName==name)
    {
      //cout<<n<<g<<endl;
      pcs.setLambda(l);
      pcs.setX(x);
      fin.close();
      return 0;
    }
  }
  fin.close();
  return 1;
}

int main()
{
    //three method to get a PaillierCrytoSystem object to do our work.
    //first
    //PaillierCryptoSystem pcs(30);//this is set the bits as 30 and generate other key automaticly.


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

    PaillierCryptoSystem pcs;
    getPriKey("shaobozhong",pcs);
    getPubKey("shaobozhong",pcs);
    PaillierPlaintext m,m1,m2;
    PaillierCiphertext c1,c2,c3;
    PaillierCiphertext cc("474415577439497500");
    cout<<pcs.dec(cc)<<endl;
    m1=99;m2=101;
    c1=pcs.enc_u(m1);
    c2=pcs.enc_u(m2);
    m1=pcs.dec(c1);
    m2=pcs.dec(c2);
    puts("sub");
    c3=pcs.subForPlain(c1,c2);
    cout<<c1<<" "<<c2<<endl;
    cout<<m1<<" "<<m2<<endl;
    cout<<c3<<endl;
    m=pcs.dec(c3);
    cout<<m<<endl;
    cout<<pcs.getActualNumber(m)<<endl;

    c3=pcs.addForPlain(c1,c2);//equal pcs.mul(c1,c2);  mul equal add in plain
    puts("add");
    cout<<c1<<" "<<c2<<endl;
    cout<<m1<<" "<<m2<<endl;
    cout<<c3<<endl;
    m=pcs.dec(c3);
    cout<<m<<endl;
    cout<<pcs.getActualNumber(m)<<endl;
    PaillierPlaintext mm=2;
    puts("mul");
    c3=pcs.mulForPlain(c1,mm);//equal pcs.exp(c1,mm);
    cout<<m1<<" "<<mm<<endl;
    cout<<c3<<endl;
    m=pcs.dec(c3);
    cout<<m<<endl;

    puts("mul negative number");
    mm=pcs.getN()-mm;
    c3=pcs.mulForPlain(c1,mm);//equal pcs.exp(c1,mm);
    cout<<m1<<" "<<mm<<endl;
    cout<<c3<<endl;
    m=pcs.dec(c3);
    cout<<m<<endl;
    cout<<pcs.getActualNumber(m)<<endl;


    return 0;
}
