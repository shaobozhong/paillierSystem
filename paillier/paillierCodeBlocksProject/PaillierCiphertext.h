#include <ostream>
#include<string>
#include<gmpxx.h>

/*
  This is a (semantic rather than strucural) type for ciphertexts.
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

#ifndef PAILLIERCIHPERTEXT_H_INCLUDED
#define PAILLIERCIHPERTEXT_H_INCLUDED
typedef mpz_class PaillierPlaintext;//use the mpz_class to save the plain texts
class PaillierCryptoSystem;
class PaillierCiphertext//use this class  to save and do some operation of paillier ciphertexts
{
    friend std::ostream& operator<<(std::ostream &out,const PaillierCiphertext& a);//friend funcfiong to overload <<
    /*
    overload "*" for mul
    but if you use this sign,you must know the result won't mod n^2
    and the mul in PaillierCryptoSystem will mod n^2
    */
    friend PaillierCiphertext operator *(const PaillierCiphertext &a, const PaillierCiphertext &b);
private:
    mpz_class data;//used to save the ciphertexts;
public:
    PaillierCiphertext();// default construct
    PaillierCiphertext(const std::string &); //construct for string
    PaillierCiphertext(const mpz_class &); //construct for mpz_class
    std::string get_str (int base = 10);
    mpz_class get_mpz_class() const;
    void set_str (const std::string& str, int base=10);
    void set_mpz_class(const mpz_class &);

    //i will implement mul and exp
};

PaillierCiphertext operator *(const PaillierCiphertext &a, const PaillierCiphertext &b);//overload "*" for mul
//because the exp need the public key ,so move it to class PaillierCryptoSystem
std::ostream &operator<<(std::ostream &out,const PaillierCiphertext& a);//friend funcfiong to overload <<


#endif // PAILLIERCIHPERTEXT_H_INCLUDED
