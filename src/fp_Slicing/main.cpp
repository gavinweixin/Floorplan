#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
//#include <sstream>
#include "NPE.h"

using namespace std;

void init(NPE &, BlockSizeMap &);
void Stockmeyer(BinNode<BlockSize> *);
void SA(NPE &, BlockSizeMap &);

int main()
{

    BlockSizeMap basicSize;

    init(str, basicSize);

    // Stockmeyer
    NPE npe(str, basicSize);
    size_t min_area = 0x7fffffff;
    vector<BlockSize> result = Stockmeyer(npe.getRoot());
    vector<BlockSize>::iterator t, i;
    for (i=result.begin(); i!=result.end(); ++i)
        if (i->first*i->second < min_area)
        {
            min_area = i->first*i->second;
            t = i;
        }
    cout << "The minimum area floorplan is "
         << t->first << "*" << t->second
         << "=" << min_area << endl;

    // Simulated Annealing
    SA(str, basicSize);

    return 0;
}

void init(string &str, BlockSizeMap &basicSize)
{
    size_t n, w, h;
	ifstream inFile("D:\\OneDrive\\Repository\\Floorplan\\testdata\\test1.in");

    // # of blocks
    inFile >> n;

    // size of blocks
    //stringstream ss;
    for (size_t i=0; i<n; i++)
    {
		inFile >> w >> h;
        //ss << i+1;
        basicSize[/*ss.str()*/to_string(i+1)] = BlockSize(w, h);
    }

    // initial design
	inFile >> str;
	inFile.close();
}


vector<BlockSize> Stockmeyer(BinNode<BlockSize> *node)
{
    vector<BlockSize> result;
    if (node->flag!="H" && node->flag!="V")
    {
        result.push_back(BlockSize(node->data.first, node->data.second));
        result.push_back(BlockSize(node->data.second, node->data.first));
        // width increase and height decrease
        if (node->data.first > node->data.second)
            reverse(result.begin(), result.end());

        return result;
    }

    vector<BlockSize> l = Stockmeyer(node->lchild);
    vector<BlockSize> r = Stockmeyer(node->rchild);

    if (node->flag == "H")
    {
		vector<BlockSize>::reverse_iterator i = l.rbegin();
		vector<BlockSize>::reverse_iterator j = r.rbegin();
        while (i!=l.rend() && j!=r.rend())
        {
            result.push_back(BlockSize(max(i->first, j->first), i->second + j->second));
            if (i->first > j->first) ++i;
            else if (i->first < j->first) ++j;
            else
            {
                ++i;
                ++j;
            }
        }
        // width increase and height decrease
        reverse(result.begin(), result.end());
    }

    if (node->flag == "V")
    {
		vector<BlockSize>::iterator i = l.begin();
		vector<BlockSize>::iterator j = r.begin();
        while (i!=l.end() && j!=r.end())
        {
            result.push_back(BlockSize(i->first + j->first, max(i->second, j->second)));
            if (i->second > j->second) ++i;
            else if (i->second < j->second) ++j;
            else
            {
                ++i;
                ++j;
            }
        }
    }

    return result;
}

void SA(string &str, BlockSizeMap &basicSize)
{

}
