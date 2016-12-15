#include <stack>
#include <algorithm>
#include "NPE.h"

using namespace std;

NPE::NPE() : BinTree<BlockSize>(), area(0) { }

NPE::NPE(const NPE &orig)
    : BinTree<BlockSize>(orig), area(orig.area), basicSize(orig.basicSize) { }

NPE::NPE(const vector<string>& tra, const BlockSizeMap& basicSize)
{
    BinNode<BlockSize> *node;
    stack<BinNode<BlockSize>*> myStack;

    for (size_t i=0; i<tra.size(); i++)
    {
        node = new(BinNode<BlockSize>);
        node->flag = tra[i];
        if (!isLeaf(node->flag))
        {
            node->rchild = myStack.top();
            myStack.pop();
            node->lchild = myStack.top();
            myStack.pop();
        } else
        {
            node->lchild = node->rchild = NULL;
            node->data = basicSize.at(node->flag);
        }
        myStack.push(node);
    }

    setRoot(myStack.top());
    setPostOrder(tra);
    this->basicSize = basicSize;
    area = 0;
}

NPE::NPE(const string& tra, const BlockSizeMap& basicSize)
{
    size_t lptr = 0, rptr;
    string str = tra + ",";
    vector<string> traversal;

    while ((rptr=str.find(',',lptr))!=string::npos)
    {
        traversal.push_back(str.substr(lptr,rptr-lptr));
		lptr = rptr + 1;
    }

    new (this)NPE(traversal, basicSize);
}

NPE::~NPE() { }

NPE& NPE::operator = (const NPE& i)
{
    setRoot(i.root);
    setPostOrder(i.postOrder);
	area = i.area;
	basicSize = i.basicSize;
    return *this;
}

// BinNode<BlockSize>* NPE::getRoot() const
// {
//     return BinTree<BlockSize>::getRoot();
// }
//
// vector<string> NPE::getPostOrder() const
// {
//     return BinTree<BlockSize>::getPostOrder();
// }

size_t NPE::getN() const
{
    return BinTree<BlockSize>::getNumLeaf();
}

size_t NPE::getArea()
{
    if (area == 0)
    {
        merge(getRoot());
        area = getRoot()->data.first * getRoot()->data.second;
    }
    return area;
}

NPE NPE::M1(size_t startPos) const
{
    vector<string> modified;
    size_t pos = startPos;

    do {
        if (pos+1 < postOrder.size())
            if (isLeaf(postOrder[pos]) && isLeaf(postOrder[pos+1]))
                //&& isLeaf(postOrder[pos+2]))
            {
                modified = postOrder;
                modified[pos] = postOrder[pos+1];
                modified[pos+1] = postOrder[pos];
                break;
            }
        pos = (pos+1) % postOrder.size();
    } while(pos!=startPos);

    // if (modified.size())
    return NPE(modified, basicSize);
    // else
    //     return NPE();
}

NPE NPE::M2(size_t startPos) const
{
    vector<string> modified;
    size_t pos = startPos;

    do {
        if (!isLeaf(postOrder[pos]))
            if (pos>0 && isLeaf(postOrder[pos-1]))
                if (pos+1<postOrder.size() && !isLeaf(postOrder[pos+1]))
                {
                    modified = postOrder;
                    while (pos < postOrder.size())
                    {
                        if (modified[pos] == "H")
                            modified[pos] = "V";
                        else if (modified[pos] == "V")
                            modified[pos] = "H";
                        else break;
                        pos++;
                    }
                    break;
                }
        pos = (pos+1) % postOrder.size();
    } while(pos!=startPos);

    // if (modified.size())
    return NPE(modified, basicSize);
    // else
    //     return NPE();
}

NPE NPE::M3(size_t startPos) const
{
    vector<string> modified;
    size_t pos = startPos;

    do {
        if (pos+1 < postOrder.size())
            if (isLeaf(postOrder[pos])+isLeaf(postOrder[pos+1]) == 1)
            {
                modified = postOrder;
                modified[pos] = postOrder[pos+1];
                modified[pos+1] = postOrder[pos];
                if (isLegalNPE(modified))
                    break;
                else
                    modified.clear();
            }
        pos = (pos+1) % postOrder.size();
    } while(pos!=startPos);

    // if (modified.size())
    return NPE(modified, basicSize);
    // else
    //     return NPE();
}

bool NPE::isLeaf(const string& str) const
{
    return (str!="H" && str!="V");
}

bool NPE::isLegalNPE(const vector<string>& npe) const
{
    size_t numOperand = 0;
    for (size_t i=0; i<npe.size(); i++)
    {
        if (isLeaf(npe[i])) numOperand++;

        // Balloting property
        if (numOperand <= i+1-numOperand)
            return false;

        // Normality property
        if (i>0 && !isLeaf(npe[i-1]) && !isLeaf(npe[i]))
            if (npe[i-1] == npe[i])
                return false;
    }
    return true;
}

void NPE::merge(BinNode<BlockSize>* node)
{
    if (node->flag!="H" && node->flag!="V") return;

    merge(node->lchild);
    merge(node->rchild);

    if (node->flag == "H")
        node->data = BlockSize(
            max(node->lchild->data.first, node->rchild->data.first),
            node->lchild->data.second + node->rchild->data.second);
    if (node->flag == "V")
        node->data = BlockSize(
            node->lchild->data.first + node->rchild->data.first,
            max(node->lchild->data.second, node->rchild->data.second));
}
