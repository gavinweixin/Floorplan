#include "NPE.h"

using namespace std;

template<class T>
NPE<T>::NPE() { }

template<class T>
NPE<T>::NPE(const NPE<T> &orig) : root(orig.root), s(orig.s) { }

template<class T>
NPE<T>::NPE(const string& orig) : BinTree<T>(orig), s(orig) { }

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