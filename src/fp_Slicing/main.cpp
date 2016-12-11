#include "fp_Slicing.h"

using namespace std;

void init(NPE &);

int main(int argc, char* argv[])
{
    NPE testcase;
    if (argc == 2)
        testcase = argv[1]; //???
    else
        init(*testcase);
    Stockmeyer(*testcase);
    SA(*testcase);
    return 0;
}

void init(NPE &design)
{
    cout << "Please type in the initial design:" << endl;
    string s;
    cin >> s;
    design = NPE(s);
    return;
}
