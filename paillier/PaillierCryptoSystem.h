#include<string>
#include<ostream>

#include<gmpxx.h>
#include"PaillierCiphertext.h"


#ifndef PAILLIER_H_INCLUDED
#define PAILLIER_H_INCLUDED



/*
  For PaillierCiphertextThis is a (semantic rather than structural) type for ciphertexts and plaintexts.
  These can also be converted to or from byte arrays (for example in
  order to store them in a file).
  but saved as mpz_class we can get some Convenience in calculate.
  and I make the ciphertexts some operations.
*/

/*
if you know how to uwe mpz_class  then you can use all operations it surport on plaintext.
Recommend:
for set and get data, since mpz_class is surport get and set by std::string ,i will implement features that from str and to str.
So i recommend you use this method to assagin and get value.
*/


typedef mpz_class PaillierPlaintext;  //use the mpz_class to save plain text


/*
    folowing code is the paillier cryptosystem calc, i am folow the algorithm on
    http://en.wikipedia.org/wiki/Paillier_cryptosystem
    I have refered to the code  on http://hms.isi.jhu.edu/acsc/libpaillier/#description.i folow the authors that  call it
    it libpaillier 0.8.
*/


class PaillierCryptoSystem
{
private:
    //public key for paillier encryption system
    int bits;  /* e.g., 1024 */
    mpz_class n;   /* public modulus n = p*q */
    mpz_class n_squared; /* cached to avoid recomputing */
    mpz_class g;//libpaillier 0.8 used the n_plusone to replace g. I want to test if the random number ok?
    mpz_class n_plusone; /* cached to avoid recomputing */

    //private key for paillier encryption system
    mpz_class lambda;    /* lambda(n), i.e., lcm(p-1,q-1) */
    mpz_class x;   /* cached to avoid recomputing  in the wikepedia it is miu*/
    //i save the p,q for study. generally they will be deleteled for security.they are useless for the rest of calculates.

    mpz_class p;
    mpz_class q;
public:
    void generateKey();
    PaillierCiphertext enc(PaillierPlaintext);
    PaillierPlaintext  dec(PaillierCiphertext);
    mpz_class getN_squared() const;
    PaillierCiphertext exp(const PaillierCiphertext &a,const PaillierPlaintext &b);//exp operation for paillierciphertexts
};




#endif // PAILLIER_H_INCLUDED
