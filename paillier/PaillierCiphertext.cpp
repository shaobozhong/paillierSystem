#include "PaillierCihpertext.h"

std::ostream & operator <<(std::ostream &out,const PaillierCiphertext& pc)
{
    out<<pc.data;
    return out;
}

void PaillierCiphertext::set_str (const std::string& str, int base)
{
    data.set_str(str,base);
}
