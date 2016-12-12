#include <stack>
#include "BinTree.h"

using namespace std;

template<class T>
BinTree<T>::BinTree() : root(NULL) { }

template<class T>
BinTree<T>::BinTree(const BinTree<T> &orig) : root(orig.root) { }

template<class T>
BinTree<T>::BinTree(const string& orig)
{
    int lptr = 0, rptr;
    BinNode *node;
    string str = orig + ",";
    stack<BinNode*> myStack;

    while ((rptr=str.find(',',lptr))!=string::npos)
    {
        node = new(BinNode);
        node->flag = substr(lptr,rptr-lptr);
        if (node->flag=="H" || node->flag=="V")
        {
            node->rchild = myStack.top();
            myStack.pop();
            node->lchild = myStack.top();
            myStack.pop();
        }
        myStack.push(node);
    }

    root = myStack.top();
}

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
BinNode<T>* BinTree<T>::getRoot() const
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
