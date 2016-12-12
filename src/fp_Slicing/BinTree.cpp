// #include <stack>
#include "BinTree.h"

using namespace std;

template<class T>
BinTree<T>::BinTree() { }

template<class T>
BinTree<T>::BinTree(const BinTree<T> &orig) : root(orig.root) { }

template<class T>
BinTree<T>::~BinTree()
{
    destruct(root);
}

template<class T>
BinTree<T>& BinTree<T>::operator = (const BinTree<T>& i)
{
    root = i.root;
    return *this;
}

template<class T>
BinNode<T>* BinTree<T>::getRoot()
{
    return root;
}

template<class T>
void BinTree<T>::destruct(BinNode<T> *node)
{
    if (node != NULL)
    {
        destruct(node->lchild);
        destruct(node->rchild);
        delete(node);
    }
}
