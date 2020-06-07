#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) 
{
    if(argc != 3)
        return 0;

    string exp(argv[1]);
    string input(argv[2]);

    regex e(exp);
    smatch sm;    // same as std::match_results<string::const_iterator> sm;
    regex_match (input,sm,e);


    int tmp1 = sm.size();
    
    if(sm.size() > 0)
    {
        int tmp2 = sm.str(0).length();
        int tmp3 = sm.str(0).size();
        cout << sm.str(0) << endl;
    }
}