#ifndef _NPE_H_
#define _NPE_H_

#include <string>

// namespace sliceDir
// {
//     enum sliceDir_
//     {
//         H = -2,     // horizontal slicing
//         V = -1      // vertical slicing
//     };
// }
// typedef sliceDir::sliceDir_ sliceDir;

template<class T>
class NPE : private BinTree<T>
{
public:
    NPE();
    NPE(const NPE<T>& orig);
    NPE(const string& orig);
    ~NPE();
    NPE<T>& operator = (const NPE<T>& i);

    // void set_pi(int i, const Interval &value);
    // int judge(double, bool=true) const;

private:
    string s;

}

#endif
