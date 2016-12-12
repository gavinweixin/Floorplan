#ifndef _BINTREE_H_
#define _BINTREE_H_

template <class T>
struct BinNode
{
    T data;
    BinNode<T> *lchild, *rchild;
};

template <class T>
class BinTree
{
public:
    BinTree();
    BinTree(const BinTree<T>& orig);
    ~BinTree();
    BinTree& operator = (const BinTree<T>& i);

    BinTree<T>* getRoot();
private:
    BinNode<T> *root;
    void destruct(BinNode<T> *node);
}

#endif
