#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
//#include <string>
#include "NPE.h"

using namespace std;

typedef map<string, pair<int,int>> myMap;
typedef vector<pair<int,int>> Stockmeyer_Datatype;

void init(string &, myMap &);
void Stockmeyer(BinNode<Stockmeyer_Datatype> *, myMap &);
void SA(string &, myMap &);

int main()
{
    string str;
    myMap block_size;

    init(str, block_size);

    // Stockmeyer
    NPE<Stockmeyer_Datatype> npe(str);
    Stockmeyer(npe.getRoot(), block_size);
    int min_area = 0x7fffffff;
    Stockmeyer_Datatype::iterator t, i;
    for (i=(npe.getRoot())->data.begin(); i!=(npe.getRoot())->data.end(); ++i)
        if (i->first*i->second < min_area)
        {
            min_area = i->first*i->second;
            t = i;
        }
    cout << "The minimum area floorplan is "
         << t->first << "*" << t->second
         << "=" << min_area << endl;

    // S A
    SA(str, block_size);

    return 0;
}

void init(string &str, myMap &block_size)
{
    int n, w, h;
    cout << "# of blocks:" << endl;
    cin >> n;
    cout << "size of blocks:" << endl;
    for (int i=0; i<n; i++)
    {
        cin >> w >> h;
        block_size[to_string(i+1)] = pair<int, int>(w, h);
    }
    cout << "Please type in the initial design:" << endl;
    cin >> str;
}


void Stockmeyer(BinNode<Stockmeyer_Datatype> *node, myMap &block_size)
{
    if (node->flag!="H" && node->flag!="V")
    {
        int w, h;
        if (block_size.count(node->flag))
        {
            w = block_size[node->flag].first;
            h = block_size[node->flag].second;
        }

        // width increase and height decrease
        node->data.push_back(pair<int, int>(w, h));
        node->data.push_back(pair<int, int>(h, w));
        if (w > h) reverse(node->data.begin(), node->data.end());

        return;
    }

    Stockmeyer(node->lchild, block_size);
    Stockmeyer(node->rchild, block_size);

    if (node->flag == "H")
    {
		Stockmeyer_Datatype::reverse_iterator i = node->lchild->data.rbegin();
		Stockmeyer_Datatype::reverse_iterator j = node->rchild->data.rbegin();
        while (i!=node->lchild->data.rend() && j!=node->rchild->data.rend())
        {
            node->data.push_back(pair<int, int>(max(i->first, j->first), i->second + j->second));
            if (i->first > j->first) ++i;
            else if (i->first < j->first) ++j;
            else
            {
                ++i;
                ++j;
            }
        }
        // width increase and height decrease
        reverse(node->data.begin(), node->data.end());
    }

    if (node->flag == "V")
    {
		Stockmeyer_Datatype::iterator i = node->lchild->data.begin();
		Stockmeyer_Datatype::iterator j = node->rchild->data.begin();
        while (i!=node->lchild->data.end() && j!=node->rchild->data.end())
        {
            node->data.push_back(pair<int, int>(i->first + j->first, max(i->second, j->second)));
            if (i->second > j->second) ++i;
            else if (i->second < j->second) ++j;
            else
            {
                ++i;
                ++j;
            }
        }
    }
}

void SA(string &str, myMap &block_size)
{

}
