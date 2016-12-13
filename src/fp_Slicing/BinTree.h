#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <string>
#include <stack>
//using std::string;
using namespace std;

template <class T>
struct BinNode
{
    T data;
    string flag;
    BinNode<T> *lchild, *rchild;
};

template <class T>
class BinTree
{
public:
    BinTree();
    BinTree(const BinTree<T>& orig);
    BinTree(const string& orig);        // input: postorder traversal divided by comma(,)
    ~BinTree();
    BinTree<T>& operator = (const BinTree<T>& i);

    void setRoot(BinNode<T>*);
    BinNode<T>* getRoot() const;

protected:
    BinNode<T> *root;

private:
    void destruct(BinNode<T> *node);
};

template<class T>
BinTree<T>::BinTree() : root(NULL) { }

template<class T>
BinTree<T>::BinTree(const BinTree<T> &orig) : root(orig.root) { }

template<class T>
BinTree<T>::BinTree(const string& orig)
{
    size_t lptr = 0, rptr;
    BinNode<T> *node;
    string str = orig + ",";
    stack<BinNode<T>*> myStack;

    while ((rptr=str.find(',',lptr))!=string::npos)
    {
        node = new(BinNode<T>);
        node->flag = str.substr(lptr,rptr-lptr);
		node->lchild = node->rchild = NULL;
        if (node->flag=="H" || node->flag=="V")
        {
            node->rchild = myStack.top();
            myStack.pop();
            node->lchild = myStack.top();
            myStack.pop();
        }
        myStack.push(node);
		lptr = rptr + 1;
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
void BinTree<T>::setRoot(BinNode<T>* node)
{
    root = node;
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

#endif
