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

    cout << sm.str(0) << endl;
}