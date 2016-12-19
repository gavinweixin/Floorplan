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

    void setRoot(BinNode<T>*);
    void setPostOrder(const vector<string>&);
    BinNode<T>* getRoot() const;
    vector<string> getPostOrder() const;
	string getPostOrderStr() const;
    size_t getNumLeaf() const;

protected:
    BinNode<T> *root;
    vector<string> postOrder;

private:
	BinNode<T>* copy(const BinNode<T> *);
    void destruct(BinNode<T> *node);
};

template<class T>
BinTree<T>::BinTree() : root(NULL) { }

template<class T>
BinTree<T>::BinTree(const BinTree<T> &orig)
    : postOrder(orig.postOrder)
{
	root = copy(orig.root);
}

template<class T>
BinNode<T>* BinTree<T>::copy(const BinNode<T> *src)
{
	if (src == NULL) return NULL;

	BinNode<T>* node = new(BinNode<T>);
	node->data = src->data;
	node->flag = src->flag;
	node->lchild = copy(src->lchild);
	node->rchild = copy(src->rchild);

	return node;
}

template<class T>
BinTree<T>::~BinTree()
{
    destruct(root);
}

template<class T>
BinTree<T>& BinTree<T>::operator = (const BinTree<T>& i)
{
    root = copy(i.root);
    postOrder = i.postOrder;
    return *this;
}

template<class T>
void BinTree<T>::setRoot(BinNode<T>* node)
{
    root = copy(node);
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
string BinTree<T>::getPostOrderStr() const
{
	string tra = postOrder[0];
	for (size_t i = 1; i < postOrder.size(); i++)
		tra = tra + "," + postOrder[i];
	return tra;
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
