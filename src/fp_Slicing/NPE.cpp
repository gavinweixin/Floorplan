#include <string>
#include "NPE.h"

using namespace std;

NPE::NPE() { }

NPE::NPE(const NPE &orig) : s(orig.s) { }

NPE::NPE(const string& orig) : s(orig) { }

NPE::~NPE() { }

NPE& NPE::operator = (const NPE& i)
{
    s = i.s;
    return *this;
}
