#include "NPE.h"

using namespace std;

template<class T>
NPE<T>::NPE() : s("") { }

template<class T>
NPE<T>::NPE(const NPE<T> &orig) : s(orig.s), root(orig.root) { }

template<class T>
NPE<T>::NPE(const string& orig) : s(orig), BinTree<T>(orig) { }

template<class T>
NPE<T>::~NPE() { }

template<class T>
NPE<T>& NPE<T>::operator = (const NPE<T>& i)
{
    s = i.s;
    root = i.root;
    return *this;
}

template<class T>
BinNode<T>* NPE<T>::getRoot() const
{
	return root;
}