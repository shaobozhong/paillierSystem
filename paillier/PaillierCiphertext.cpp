#include "PaillierCiphertext.h"

PaillierCiphertext::PaillierCiphertext()
{

}

PaillierCiphertext::PaillierCiphertext(const std::string &str)
{
    this->set_str(str);
}

PaillierCiphertext::PaillierCiphertext(const mpz_class &mpz)
{
    this->set_mpz_class(mpz);
}


PaillierCiphertext operator *(const PaillierCiphertext &a,const PaillierCiphertext &b)//overload "*" for mul
{
    mpz_class tmpRes;
    tmpRes=a.get_mpz_class()*b.get_mpz_class();
    PaillierCiphertext res(tmpRes);
    return res;
}



std::ostream & operator <<(std::ostream &out,const PaillierCiphertext& pc)
{
    out<<pc.data;
    return out;
}

void PaillierCiphertext::set_str (const std::string& str, int base)
{
    data.set_str(str,base);
}


void PaillierCiphertext::set_mpz_class(const mpz_class &mpz)
{
    data=mpz;
}

mpz_class PaillierCiphertext::get_mpz_class() const
{
    return data;
}

std::string PaillierCiphertext::get_str(int base)
{
    return data.get_str(base);
}


