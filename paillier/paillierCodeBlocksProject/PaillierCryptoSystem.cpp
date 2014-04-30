#include"PaillierCryptoSystem.h"

PaillierCryptoSystem::PaillierCryptoSystem()
{
    setBits(0);
    setN("0");
    setG("0");
    setN_plusnoe("0");
    setN_squared("0");
    setLambda("0");
    setX("0");
}


PaillierCryptoSystem::PaillierCryptoSystem(int modulusbits)
{
    generateKey_u(modulusbits);
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


mpz_class PaillierCryptoSystem::getP()const
{
    return p;
}

mpz_class PaillierCryptoSystem::getQ()const
{
    return q;
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



void PaillierCryptoSystem::setP(const mpz_class &p)
{
    this->p=p;
}

void PaillierCryptoSystem::setQ(const mpz_class &q)
{
    this->q=q;
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



void PaillierCryptoSystem::paillier_get_rand_file(byte  * buf, int len, const std::string &file )
{
    FILE* fp;
    byte *p;

    fp = fopen(file.c_str(), "r");

    p = (byte *)buf;
    while( len )
    {
        size_t s;
        s = fread(p, 1, len, fp);
        p += s;
        len -= s;
    }

    fclose(fp);
}


void PaillierCryptoSystem::paillier_get_rand_devrandom(byte* buf, int len )
{
    paillier_get_rand_file(buf, len, "/dev/random");
}

void PaillierCryptoSystem::paillier_get_rand_devurandom(byte* buf, int len )
{
    paillier_get_rand_file(buf, len, "/dev/urandom");
}


void PaillierCryptoSystem::init_rand(gmp_randclass &gmpR, int bytes)
{
    byte* buf;
    mpz_t tmps;
    buf =(byte*) malloc(bytes);
    paillier_get_rand_devrandom(buf, bytes);
    mpz_init(tmps);
    mpz_import(tmps, bytes, 1, 1, 0, 0, buf);
    mpz_class s(tmps);
    gmpR.seed(s);
    mpz_clear(tmps);
    free(buf);
}

void PaillierCryptoSystem::init_rand_u(gmp_randclass &gmpR, int bytes)
{
    byte* buf;
    mpz_t tmps;
    buf = (byte*)malloc(bytes);
    paillier_get_rand_devurandom(buf, bytes);
    mpz_init(tmps);
    mpz_import(tmps, bytes, 1, 1, 0, 0, buf);
    mpz_class s(tmps);
    gmpR.seed(s);
    mpz_clear(tmps);
    free(buf);
}










PaillierCiphertext PaillierCryptoSystem::mul(const PaillierCiphertext &a,const PaillierCiphertext &b)//overload "*" for mul
{
    if(!checkKey())//if key is not well then the key is not ready then return -1 as the result.
    {
        return PaillierCiphertext("-1");
    }
    mpz_class tmpRes;
    tmpRes=(a.get_mpz_class()*b.get_mpz_class())%n_squared;
    PaillierCiphertext res(tmpRes);
    return res;
}


PaillierCiphertext PaillierCryptoSystem::exp(const PaillierCiphertext &a,const PaillierPlaintext &b)//exp operation for paillierciphertexts ^ plaintext
{
    if(!checkKey())//if key is not well then the key is not ready then return -1 as the result.
    {
        return PaillierCiphertext("-1");
    }
    mpz_t tmp;
    mpz_init(tmp);

    mpz_powm(tmp, a.get_mpz_class().get_mpz_t(), b.get_mpz_t(),n_squared.get_mpz_t());//calc (a^b)%n^2
    mpz_class tmpRes=mpz_class(tmp);
    mpz_clear(tmp);
    return PaillierCiphertext(tmpRes);
}

void PaillierCryptoSystem::completeKey_u()
{
    if(p==0 && q==0) return;//if p,q is not ready cannot complete the key
    //pubkey
    n_plusone=n-1;
    n_squared=n*n;
    //g
    gmp_randclass gmpR(gmp_randinit_default);
    init_rand_u(gmpR,bits);
    g=gmpR.get_z_range(n_squared);//if necessary can be gmpR.get_z_range(n_squared-1)+1 then will be 1->n-1

    //privatekey
    mpz_class p_1,q_1;
    p_1=p-1;
    q_1=q-1;
    mpz_t tmp;
    mpz_init(tmp);
    mpz_lcm(tmp, p_1.get_mpz_t(), q_1.get_mpz_t());

    lambda=mpz_class(tmp);
    mpz_powm(tmp, g.get_mpz_t(), lambda.get_mpz_t(),n_squared.get_mpz_t());
	mpz_sub_ui(tmp, tmp, 1);
	mpz_div(tmp, tmp, n.get_mpz_t());
	mpz_invert(tmp,tmp,n.get_mpz_t());
    x=mpz_class(tmp);
	mpz_clear(tmp);

}

void PaillierCryptoSystem::completeKey()
{
      if(p==0 && q==0) return;//if p,q is not ready cannot complete the key
        //pubkey
    n_plusone=n-1;
    n_squared=n*n;
    //g
    gmp_randclass gmpR(gmp_randinit_default);
    init_rand(gmpR,bits);
    g=gmpR.get_z_range(n_squared);//if necessary can be gmpR.get_z_range(n_squared-1)+1 then will be 1->n-1
    //privatekey
    mpz_class p_1,q_1;
    p_1=p-1;
    q_1=q-1;
    mpz_t tmp;
    mpz_init(tmp);


    mpz_lcm(tmp, p_1.get_mpz_t(), q_1.get_mpz_t());
    lambda=mpz_class(tmp);
    mpz_powm(tmp, n_plusone.get_mpz_t(), lambda.get_mpz_t(),n_squared.get_mpz_t());
	mpz_sub_ui(tmp, tmp, 1);
	mpz_div(tmp, tmp, n.get_mpz_t());
	mpz_invert(tmp,tmp,n.get_mpz_t());
    x=mpz_class(tmp);
	mpz_clear(tmp);
}


bool PaillierCryptoSystem::checkKey()
{

    if(bits==0) return false;
    if (n==0) return false;
    if (g==0) return false;
    if(n_plusone==0) return false;
    if (n_squared==0) return false;
    if(lambda==0) return false;
    if(x==0) return false;
    if (!mpz_tstbit(n.get_mpz_t(), bits - 1)) return false;//if the n's bits is not right
    if (mpz_probab_prime_p(p.get_mpz_t(), 10)==0) return false;
    if (mpz_probab_prime_p(q.get_mpz_t(), 10)==0) return false;
    if (g<0 || g>n_squared) return false;
    mpz_class tmpLambda,tmpX;
    mpz_t tmp;
    mpz_init(tmp);

    mpz_class p_1,q_1;
    p_1=p-1;
    q_1=q-1;
    mpz_lcm(tmp, p_1.get_mpz_t(), q_1.get_mpz_t());
    tmpLambda=mpz_class(tmp);
    if(lambda!=tmpLambda) return false;
    mpz_powm(tmp, g.get_mpz_t(), lambda.get_mpz_t(),n_squared.get_mpz_t());
	mpz_sub_ui(tmp, tmp, 1);
	mpz_div(tmp, tmp, n.get_mpz_t());
	mpz_invert(tmp,tmp,n.get_mpz_t());
    tmpX=mpz_class(tmp);
	mpz_clear(tmp);
    if (x!=tmpX) return false;
    return true;
}

void PaillierCryptoSystem::generateKey_u(int modulusbits)
{

    gmp_randclass gmpR(gmp_randinit_default);//use the default algorithm to generate random num
    bits=modulusbits;
    /* pick random (modulusbits/2)-bit primes p and q */
    init_rand_u(gmpR, bits / 8 + 1);
    do
    {
        do
            p=gmpR.get_z_bits(bits/2);
        while(mpz_probab_prime_p(p.get_mpz_t(), 10)==0 );

        do
            q=gmpR.get_z_bits(bits/2);
        while(mpz_probab_prime_p(q.get_mpz_t(), 10)==0);
        /* compute the public modulus n = p q */
        n=p*q;
    }
    while( !mpz_tstbit(n.get_mpz_t(), bits - 1));  //make sure that the (bits-1)th bit is 1
    completeKey_u();
}


void PaillierCryptoSystem::generateKey(int modulusbits)
{

    gmp_randclass gmpR(gmp_randinit_default);//use the default algorithm to generate random num
    bits=modulusbits;
    /* pick random (modulusbits/2)-bit primes p and q */
    init_rand(gmpR, bits / 8 + 1);
    do
    {
        do
            p=gmpR.get_z_bits(bits/2);
        while(mpz_probab_prime_p(p.get_mpz_t(), 10)==0 );

        do
            q=gmpR.get_z_bits(bits/2);
        while(mpz_probab_prime_p(q.get_mpz_t(), 10)==0);
        /* compute the public modulus n = p q */
        n=p*q;
    }
    while( !mpz_tstbit(n.get_mpz_t(), bits - 1));  //make sure that the (bits-1)th bit is 1
    completeKey_u();
}

PaillierCiphertext PaillierCryptoSystem::enc_u(PaillierPlaintext pt)
{
    if(!checkKey())//if key is not well then the key is not ready then return -1 as the result.
    {
        return PaillierCiphertext("-1");
    }



    mpz_t tmp;
    mpz_init(tmp);
    mpz_class r;
    gmp_randclass gmpR(gmp_randinit_default);
 	init_rand_u(gmpR, bits / 8 + 1);

	do{

        r=gmpR.get_z_range(n);
        mpz_gcd(tmp,r.get_mpz_t(),n.get_mpz_t());

       }while(mpz_cmp_ui(tmp,1)!=0);

	/* compute ciphertext */

    mpz_class tmpRes;
	mpz_powm(tmp, g.get_mpz_t(), pt.get_mpz_t(),n_squared.get_mpz_t());
	tmpRes=mpz_class(tmp);
	mpz_powm(tmp, r.get_mpz_t(), n.get_mpz_t(),n_squared.get_mpz_t());
	tmpRes=tmpRes*mpz_class(tmp);
	tmpRes=tmpRes%n_squared;

    mpz_clear(tmp);
    PaillierCiphertext res;
    res=tmpRes;
    return res;
}


PaillierCiphertext PaillierCryptoSystem::enc(PaillierPlaintext pt)
{
    if(!checkKey())//if key is not well then the key is not ready then return -1 as the result.
    {
        return PaillierCiphertext("-1");
    }



    mpz_t tmp;
    mpz_init(tmp);
    mpz_class r;
    gmp_randclass gmpR(gmp_randinit_default);
 	init_rand(gmpR, bits / 8 + 1);

	do{

        r=gmpR.get_z_range(n);
        mpz_gcd(tmp,r.get_mpz_t(),n.get_mpz_t());

       }while(mpz_cmp_ui(tmp,1)!=0);

	/* compute ciphertext */

    mpz_class tmpRes;
	mpz_powm(tmp, g.get_mpz_t(), pt.get_mpz_t(),n_squared.get_mpz_t());
	tmpRes=mpz_class(tmp);
	mpz_powm(tmp, r.get_mpz_t(), n.get_mpz_t(),n_squared.get_mpz_t());
	tmpRes=tmpRes*mpz_class(tmp);
	tmpRes=tmpRes%n_squared;

    mpz_clear(tmp);
    PaillierCiphertext res;
    res=tmpRes;
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
    if(!checkKey())//if key is not well then the key is not ready then return -1 as the result.
    {
        return PaillierPlaintext("-1");
    }
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


PaillierCiphertext PaillierCryptoSystem::addForPlain(const PaillierCiphertext &a,const PaillierCiphertext &b)
{
    return this->mul(a,b);
}


PaillierCiphertext PaillierCryptoSystem::mulForPlain(const PaillierCiphertext &c,const PaillierPlaintext &m)
{
    return this->exp(c,m);
}


 PaillierCiphertext PaillierCryptoSystem::subForPlain(const PaillierCiphertext &a,const PaillierCiphertext &b)
 {

    PaillierPlaintext n_1=n-1;//represent -1
    PaillierCiphertext tmpB=this->exp(b,n_1);//b=b*-1
    return this->mul(a,tmpB);
 }

PaillierPlaintext PaillierCryptoSystem::getActualNumber(const PaillierPlaintext &pt)
{
    if (pt>n/2) return pt-n;
    return pt;
}

PaillierPlaintext PaillierCryptoSystem::setNegativeNumbertoPositiveNumber(const PaillierPlaintext &pt)
{
    if (pt<0) return n-pt;
    return pt;
}

