#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <string>

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

    BinNode<T>* getRoot();

protected:
    BinNode<T> *root;

private:
    void destruct(BinNode<T> *node);
}

#endif
