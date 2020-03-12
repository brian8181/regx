#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) 
{
    if(argc != 3)
        return 0;

    string exp(argv[1]);
    string src(argv[2]);

    string FG_GREEN = "\e[32m";
    string UNDERLINE = "\e[4m";
    string BOLD = "\e[1m";
    string RESET_FORMAT = "\e[0m";
    string CURRENT_FG_COLOR = FG_GREEN + UNDERLINE;
       
    cout << "\n" << BOLD << "regx" << RESET_FORMAT << " " 
         << UNDERLINE << "PATTERN" << RESET_FORMAT << " " 
         << UNDERLINE << "INPUT"   << RESET_FORMAT << "\n";

    cout << "pattern: " << "\"" << exp << "\"" << " -> " 
         << "input: " << "\"" << src << "\"" << endl;

    int idx = 0;
    string bash_str = src;
    regex tags_regx(exp);
    auto begin = sregex_iterator(src.begin(), src.end(), tags_regx);
    auto end = sregex_iterator();
    
    for (sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
                
        int pos = match.position() + (idx * (CURRENT_FG_COLOR.length() + RESET_FORMAT.length()));
        int len = match.length();

        // set bash green start postion
        bash_str.insert(pos, CURRENT_FG_COLOR);

        // reset bash color position
        pos = pos + CURRENT_FG_COLOR.length() + len;
        bash_str.insert(pos, RESET_FORMAT);
       
        ++idx;
    }

    cout << "\nFound " << std::distance(begin, end) << " matches:\n";
    cout << bash_str << "\n\n";
}