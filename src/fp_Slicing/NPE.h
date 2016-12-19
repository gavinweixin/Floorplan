#ifndef _NPE_H_
#define _NPE_H_

#include <string>
#include <map>
#include <cstddef>
#include "BinTree.h"

typedef pair<size_t,size_t> BlockSize;
typedef map<string, BlockSize> BlockSizeMap;

class NPE : public BinTree<BlockSize>
{
public:
    NPE();
    NPE(const NPE& orig);
    NPE(const vector<string>&, const BlockSizeMap&);
    NPE(const string&, const BlockSizeMap&); // input: postorder traversal divided by comma(,)
    ~NPE();
    NPE& operator = (const NPE& i);

    size_t getN() const;
    size_t getArea();

    NPE M1(size_t startPos) const;
    NPE M2(size_t startPos) const;
    NPE M3(size_t startPos) const;

private:
    bool isLeaf(const string&) const;
    bool isLegalNPE(const vector<string>&) const;
    void merge(BinNode<BlockSize>*);

    size_t area;
    BlockSizeMap basicSize;
};

#endif
