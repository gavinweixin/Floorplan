#ifndef _NPE_H_
#define _NPE_H_

#include <string>
#include "BinTree.h"

using namespace std;
//using std::string;

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
class NPE : public BinTree<T>
{
public:
    NPE();
    NPE(const NPE<T>& orig);
    NPE(const string& orig);
    ~NPE();
    NPE<T>& operator = (const NPE<T>& i);

	BinNode<T>* getRoot() const;
    // void set_pi(int i, const Interval &value);
    // int judge(double, bool=true) const;

private:
    string s;

};

template<class T>
NPE<T>::NPE() : s("") { }

template<class T>
NPE<T>::NPE(const NPE<T> &orig) : BinTree<T>(orig), s(orig.s) { }

template<class T>
NPE<T>::NPE(const string& orig) : BinTree<T>(orig), s(orig) { }

template<class T>
NPE<T>::~NPE() { }

template<class T>
NPE<T>& NPE<T>::operator = (const NPE<T>& i)
{
    s = i.s;
//    BinTree<T>::root = i.root; //????
    setRoot(i.root);
    return *this;
}

template<class T>
BinNode<T>* NPE<T>::getRoot() const
{
    return BinTree<T>::getRoot();
}

#endif
