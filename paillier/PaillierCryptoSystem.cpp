#include"PaillierCryptoSystem.h"



PaillierPlaintext  PaillierCryptoSystem::dec(PaillierCiphertext ct)//dec operation
{
    PaillierPlaintext res;
    mpz_t tmp;
    mpz_init(tmp);
    mpz_powm(tmp, ct.get_mpz_class().get_mpz_t(), lambda.get_mpz_t(), n_squared.get_mpz_t());// wait test

//    mpz_powm(res->m, ct->c, prv->lambda, pub->n_squared);
//    mpz_sub_ui(res->m, res->m, 1);
//    mpz_div(res->m, res->m, pub->n);
//    mpz_mul(res->m, res->m, prv->x);
//    mpz_mod(res->m, res->m, pub->n);
return res;
}

mpz_class PaillierCryptoSystem::getN_squared() const
{
    return n_squared;
}

PaillierCiphertext PaillierCryptoSystem::exp(const PaillierCiphertext &a,const PaillierPlaintext &b)//exp operation for paillierciphertexts ^ plaintext
{
    mpz_t tmp;
    mpz_init(tmp);

    mpz_powm(tmp, a.get_mpz_class().get_mpz_t(), b.get_mpz_t(),n_squared.get_mpz_t());//calc (a^b)%n^2
    mpz_class tmpRes=mpz_class(tmp);
    mpz_clear(tmp);
    return PaillierCiphertext(tmpRes);
}

