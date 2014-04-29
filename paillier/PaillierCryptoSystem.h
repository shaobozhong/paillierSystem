#include<string>
#include<ostream>

#include<gmpxx.h>
#include "PaillierCiphertext.h"
#include "PaillierPlaintext.h"


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


/*
    Note:
        for the random number 's seed there are two method to get,one is /dev/random and another is /dev/urandom
        the /dev/random is more randomness,but is too slow,my recomands is use the /dev/urandom
        in our code is the function followed by postfix _u
*/

typedef unsigned char byte;

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

    /*
        these function to init the parameter of gmp's random integer  function
    */
    //read form /dev/random or /dev/urandom file
    void paillier_get_rand_file( byte* buf, int len, const std::string &file );
    //get a len*bytes randomnum from /dev/random
    void paillier_get_rand_devrandom( byte* buf, int len );
    //get a len*bytes randomnum from /dev/urandom
    void paillier_get_rand_devurandom( byte* buf, int len );
    //this funtion get the random seed from /dev/urandom
    void init_rand_u(gmp_randclass &gmpR,int bytes);
    //this funtion get the random seed from /dev/random
    void init_rand(gmp_randclass &gmpR,int bytes);


public:
    /*
        construtors
        if you assign one value then you must assign all value except for p and q.because p and q are not need by all operation.

    */
    //if no paramaters then set all attributes to zero
    PaillierCryptoSystem();
    //assign only the bits of key n and will automatic generate the key
    PaillierCryptoSystem(int modulusbits);

    //assgign all value except for p and q.
    PaillierCryptoSystem(int bits,const mpz_class &n,const mpz_class &n_squared,
    const mpz_class &g,const mpz_class &n_plusone,const mpz_class &lambda,const mpz_class &x);
    //for simple i surport the string as the parameters as big integers
    PaillierCryptoSystem(int bits,const std::string &n,const std::string &n_squared,
    const std::string &g,const std::string &n_plusone,const std::string &lambda,const std::string &x);


    /*
        these are getters and setters
    */
    int getBits() const;
    mpz_class getN()const ;
    mpz_class getN_squared() const;
    mpz_class getG() const;
    mpz_class getN_plusone()const ;
    mpz_class getLambda()const;
    mpz_class getX()const;
    mpz_class getP()const;
    mpz_class getQ()const;

    void setBits(int);
    void setN(const mpz_class &);
    void setN_squared(const mpz_class &);
    void setG(const mpz_class &);
    void setN_plusnoe(const mpz_class &);
    void setLambda(const mpz_class &);
    void setX(const mpz_class &);
    void setP(const mpz_class &);
    void setQ(const mpz_class &);

    //surport the string as bit integers parameters
    void setN(const std::string &);
    void setN_squared(const std::string &);
    void setG(const std::string &);
    void setN_plusnoe(const std::string &);
    void setLambda(const std::string &);
    void setX(const std::string &);

    /*
        mul operation for paillierciphertexts.The result has been mod n^2,then is in the Zn^2 ring
        you must know the difference between this function and the overload sign '*' in Class PaillierCiphertext
    */
    PaillierCiphertext mul(const PaillierCiphertext &a,const PaillierCiphertext &b);
    /*
        exp operation for paillierciphertexts.The result has been mod n^2,then is in the Zn^2 ring
    */
    PaillierCiphertext exp(const PaillierCiphertext &a,const PaillierPlaintext &b);


    /*
    this function complete the key after generate the p,q and the generate the g based on /dev/random
    */
    void completeKey();
    /*
    this function complete the key after generate the p,q and the generate the g based on /dev/urandom
    */
    void completeKey_u();
    /*
        this funciton generate the key of Paillier algorithm
    */
    void generateKey(int modulusbits);
    void generateKey_u(int modulusbits);


    /*
        this function is designed to check if all key is ok
    */

    bool checkKey();
    /*
        this function finish the task that convert the plaintext to ciphertext.
        the random number r 's seed is generate by /dev/urandom
    */
    PaillierCiphertext enc(PaillierPlaintext);

        /*
        this function finish the task that convert the plaintext to ciphertext.
        the random number r 's seed is generate by /dev/random
    */
    PaillierCiphertext enc_u(PaillierPlaintext);
    /*
        this function finish the task that convert the ciphertext to plaintext.
    */
    PaillierPlaintext  dec(PaillierCiphertext);

};




#endif // PAILLIER_H_INCLUDED
