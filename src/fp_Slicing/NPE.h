#ifndef _NPE_H_
#define _NPE_H_

#include <string>
#include "BinTree.h"

typedef pair<size_t,size_t> BlockSize;
typedef map<string, BlockSize> BlockSizeMap;
// namespace sliceDir
// {
//     enum sliceDir_
//     {
//         H = -2,     // horizontal slicing
//         V = -1      // vertical slicing
//     };
// }
// typedef sliceDir::sliceDir_ sliceDir;

class NPE : public BinTree<BlockSize>
{
public:
    NPE();
    NPE(const NPE& orig);
    NPE(const vector<string>&, const BlockSizeMap&);
    NPE(const string&, const BlockSizeMap&); // input: postorder traversal divided by comma(,)
    ~NPE();
    NPE& operator = (const NPE& i);

	// BinNode<BlockSize>* getRoot() const;
    // vector<string> getPostOrder() const;
    size_t getN() const;
    size_t getArea() const;

    NPE M1(size_t startPos) const;
    NPE M2(size_t startPos) const;
    NPE M3(size_t startPos) const;

private:
    bool isLeaf(const string&) const;
    bool isLegalNPE(const vector<string>&) const;
    void merge(const BinNode<BlockSize>*);

    size_t area;
    BlockSizeMap basicSize;

};


#endif
