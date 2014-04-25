#include <ostream>

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

class PaillierCiphertext//use this class  to save and do some operation of paillier ciphertexts
{
    friend std::ostream& operator<<(std::ostream &out,const PaillierCiphertext& a);//friend funcfiong to overload <<
    friend PaillierCiphertext operator *(const PaillierCiphertext &a,const PaillierCiphertext &b);//
    friend PaillierCiphertext operator ^(const PaillierCiphertext &a,const PaillierPlaintext &b);//
    private:
        mpz_class data;//used to save the ciphertexts;
    public:
    std::string get_str (int base = 10);
    void set_str (const std::string& str, int base=10);
    void set_mpz_class(const mpz_class&);
    //i will implement mul and exp
};


std::ostream &operator<<(std::ostream &out,const PaillierCiphertext& a);//friend funcfiong to overload <<

#endif // PAILLIERCIHPERTEXT_H_INCLUDED
