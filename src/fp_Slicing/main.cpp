#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

//#include <sstream>
#include "NPE.h"

// #define RAND_MAX 0x7fff

using namespace std;

NPE init();
vector<BlockSize> Stockmeyer(BinNode<BlockSize> *);
NPE SA(NPE &);

int main()
{

    NPE npe = init();

    // Stockmeyer
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
    double freezingPoint = 1e-100;
    double r = 0.85;
    size_t k = 10; // k <- 5~10 suggested
    NPE optimized = SA(npe, freezingPoint, r, k);
    cout << "The optimized floorplan is "
         << optimized.getPostOrderStr() << endl;
    cout << "Aera: "
         << (optimized.getRoot())->data.first << "*" << (optimized.getRoot())->data.second
         << "=" << (optimized.getRoot())->data.first*(optimized.getRoot())->data.second
         << endl;

    return 0;
}

NPE init()
{
    size_t n, w, h;
	string str;
	ifstream inFile("D:\\Sync\\Repository\\Floorplan\\testdata\\test1.in");

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

    return NPE(str, basicSize);
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

NPE SA(NPE &npe, double freezingPoint, double r, size_t k)
{
    NPE best(npe), E(npe), NE;
    size_t n = npe.getN();
    size_t N = k*n;
    double T = 1e4;
    size_t M, MT, uphill;
    size_t startPos, delta;

    while ((double)reject/MT<0.95 && T>freezingPoint) //????
    {
        MT = uphill = reject = 0;
        while (uphill<N && MT<2*N)
        {
            M = rand() % 3 + 1;
            startPos = rand() % n;
            switch (M)
            {
            case 1: NE = E.M1(startPos); break;
            case 2: NE = E.M2(startPos); break;
            case 3: NE = E.M3(startPos); break;
            default:
            }

            // selected kind of move not feasible
            // if (!NE.getN()) continue;

            MT++;
            delta = NE.getArea() - E.getArea();
            if (delta<=0 || (double)rand()/RAND_MAX < exp(-delta/T))
            {
                if (delta > 0) uphill++;
                E = NE;
                if (E.getArea() < best.getArea())
                    best = E;
            }
            else reject++;
        }
        T = r * T;
    }

    return best;
}
