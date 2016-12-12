#ifndef _NPE_H_
#define _NPE_H_

namespace sliceDir
{
    enum sliceDir_
    {
        H = -2,     // horizontal slicing
        V = -1      // vertical slicing
    };
}
typedef sliceDir::sliceDir_ sliceDir;

class NPE : private BinTree
{
public:
    NPE();
    NPE(const NPE& orig);
    NPE(const string& orig);
    ~NPE();
    NPE& operator = (const NPE& i);

    // double volume_cal () const;
    // void set_pi(int i, const Interval &value);
    // int judge(double, bool=true) const;

private:
    string s;

}

#endif
