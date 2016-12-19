#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "NPE.h"

using namespace std;

NPE init(char *);
vector<BlockSize> Stockmeyer(BinNode<BlockSize> *);
NPE SA(NPE &, double, double, size_t);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "usage: floorplan input_file" << endl;
		return 1;
	}

    NPE npe = init(argv[1]);

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
	cout << "================Stockmeyer=================" << endl;
    cout << "minimum area:\t"
         << t->first << "*" << t->second
         << "=" << min_area << endl;

    // Simulated Annealing
    double freezingPoint = 1e-10;
    double r = 0.85;
    size_t k = 10; // k = 5~10 suggested
	cout << endl << "============Simulated Annealing============" << endl;
	npe.getArea();
	cout << "initial design:\t" << npe.getPostOrderStr()
		<< "\tarea=" << (npe.getRoot())->data.first << "*" << (npe.getRoot())->data.second
		<< "=" << (npe.getRoot())->data.first*(npe.getRoot())->data.second
		<< endl;
    NPE optimized = SA(npe, freezingPoint, r, k);
	
    cout << "opt design:\t"
         << optimized.getPostOrderStr();
    cout << "\taera="
         << (optimized.getRoot())->data.first << "*" << (optimized.getRoot())->data.second
         << "=" << (optimized.getRoot())->data.first*(optimized.getRoot())->data.second
         << endl;

    return 0;
}

NPE init(char *filename)
{
    size_t n, w, h;
	string str;
	ifstream inFile(filename);

    // # of blocks
    inFile >> n;

    // size of blocks
	BlockSizeMap basicSize;
    for (size_t i=0; i<n; i++)
    {
		inFile >> w >> h;
        basicSize[to_string(i+1)] = BlockSize(w, h);
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
    size_t M, MT=1, uphill, reject=0;
    size_t startPos;
	int delta;

    while ((double)reject/MT<0.95 && T>freezingPoint)
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
			default:;
			}
            MT++;
            delta = NE.getArea() - E.getArea();
            if (delta<=0 || (double)rand()/RAND_MAX < exp(-delta/T))
            {
                if (delta > 0) uphill++;
                E = NE;
				if (E.getArea() < best.getArea())
				{
					cout << "better design:\t" << E.getPostOrderStr()
						<< "\tarea=" << (E.getRoot())->data.first << "*" << (E.getRoot())->data.second
						<< "=" << (E.getRoot())->data.first*(E.getRoot())->data.second
						<< endl;
					best = E;
				}
            }
            else reject++;
        }
        T = r * T;
    }

    return best;
}
