#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <string>
#include <vector>

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
    ~BinTree();
    BinTree<T>& operator = (const BinTree<T>& i);

    void setRoot(const BinNode<T>*);
    void setPostOrder(const vector<string>&);
    BinNode<T>* getRoot() const;
    vector<string> getPostOrder() const;
    size_t getNumLeaf() const;

protected:
    BinNode<T> *root;
    vector<string> postOrder;

private:
    void destruct(BinNode<T> *node);
};

template<class T>
BinTree<T>::BinTree() : root(NULL) { }

template<class T>
BinTree<T>::BinTree(const BinTree<T> &orig)
    : root(orig.root), postOrder(orig.postOrder) { }

template<class T>
BinTree<T>::~BinTree()
{
    destruct(root);
}

template<class T>
BinTree<T>& BinTree<T>::operator = (const BinTree<T>& i)
{
    root = i.root;
    postOrder = i.postOrder;
    return *this;
}

template<class T>
void BinTree<T>::setRoot(const BinNode<T>* node)
{
    root = node;
}

template<class T>
void BinTree<T>::setPostOrder(const vector<string> &tra)
{
    postOrder = tra;
}

template<class T>
BinNode<T>* BinTree<T>::getRoot() const
{
    return root;
}

template<class T>
vector<string> BinTree<T>::getPostOrder() const
{
    return postOrder;
}

template<class T>
size_t BinTree<T>::getNumLeaf() const
{
    return (postOrder.size()+1)/2;
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
