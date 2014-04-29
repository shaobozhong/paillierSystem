#include"PaillierCryptoSystem.h"

PaillierCryptoSystem::PaillierCryptoSystem()
{
    this->generateKey();
}


PaillierCryptoSystem::PaillierCryptoSystem(int bits,const mpz_class &n,const mpz_class &n_squared,
    const mpz_class &g,const mpz_class &n_plusone,const mpz_class &lambda,const mpz_class &x)
{
    setBits(bits);
    setN(n);
    setN_squared(n_squared);
    setG(g);
    setN_plusnoe(n_plusone);
    setLambda(lambda);
    setX(x);
}

// for simple i only surport solution whtn the base =10.
PaillierCryptoSystem::PaillierCryptoSystem(int bits,const std::string &n,const std::string &n_squared,
    const std::string &g,const std::string &n_plusone,const std::string &lambda,const std::string &x)
{
    setBits(bits);
    setN(n);
    setN_squared(n_squared);
    setG(g);
    setN_plusnoe(n_plusone);
    setLambda(lambda);
    setX(x);
}


int PaillierCryptoSystem::getBits() const
{
    return bits;
}

mpz_class PaillierCryptoSystem::getN() const
{
    return n;
}

mpz_class PaillierCryptoSystem::getN_squared() const
{
    return n_squared;
}

mpz_class PaillierCryptoSystem::getG() const
{
    return g;
}
mpz_class PaillierCryptoSystem::getN_plusone()const
{
    return n_plusone;
}
mpz_class PaillierCryptoSystem::getLambda()const
{
    return lambda;
}
mpz_class PaillierCryptoSystem::getX()const
{
    return x;
}



void PaillierCryptoSystem::setBits(int bits)
{
    this->bits=bits;
}
void PaillierCryptoSystem::setN(const mpz_class &n)
{
    this->n=n;
}
void PaillierCryptoSystem::setN_squared(const mpz_class &n_squared)
{
    this->n_squared=n_squared;
}
void PaillierCryptoSystem::setG(const mpz_class &g)
{
    this->g=g;
}
void PaillierCryptoSystem::setN_plusnoe(const mpz_class &n_plusone)
{
    this->n_plusone=n_plusone;
}

void PaillierCryptoSystem::setLambda(const mpz_class &lambda)
{
    this->lambda=lambda;
}
void PaillierCryptoSystem::setX(const mpz_class &x)
{
    this->x=x;
}



void PaillierCryptoSystem::setN(const std::string &n)
{
    this->n.set_str(n,10);
}
void PaillierCryptoSystem::setN_squared(const std::string &n_squared)
{
    this->n_squared.set_str(n_squared,10);
}
void PaillierCryptoSystem::setG(const std::string &g)
{
    this->g.set_str(g,10);
}
void PaillierCryptoSystem::setN_plusnoe(const std::string &n_plusone)
{
   this->n_plusone.set_str(n_plusone,10);
}

void PaillierCryptoSystem::setLambda(const std::string &lambda)
{
    this->lambda.set_str(lambda,10);
}
void PaillierCryptoSystem::setX(const std::string &x)
{
    this->x.set_str(x,10);
}


PaillierCiphertext PaillierCryptoSystem::mul(const PaillierCiphertext &a,const PaillierCiphertext &b)//overload "*" for mul
{
    mpz_class tmpRes;
    tmpRes=(a.get_mpz_class()*b.get_mpz_class())%n_squared;
    PaillierCiphertext res(tmpRes);
    return res;
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


void PaillierCryptoSystem::generateKey()
{

}

PaillierCiphertext PaillierCryptoSystem::enc(PaillierPlaintext)
{
    PaillierCiphertext res;
    return res;
}

PaillierPlaintext  PaillierCryptoSystem::dec(PaillierCiphertext ct)//dec operation
{
    /*
    Formula:m=L(c^labamda)*x % N
    this is the code in the libpaillier 0.8
        mpz_powm(res->m, ct->c, prv->lambda, pub->n_squared);
        mpz_sub_ui(res->m, res->m, 1);
        mpz_div(res->m, res->m, pub->n);
        mpz_mul(res->m, res->m, prv->x);
        mpz_mod(res->m, res->m, pub->n);
    */

    mpz_t tmp;
    mpz_init(tmp);
    mpz_powm(tmp, ct.get_mpz_class().get_mpz_t(), lambda.get_mpz_t(), n_squared.get_mpz_t());
    PaillierPlaintext res(tmp);
    res=res-1;
    res=res/this->n;
    res=res*this->x;
    res=res%this->n;
    return res;
}



