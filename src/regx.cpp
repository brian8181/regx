#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) 
{
    if(argc != 3)
        return -1; // args error

    string exp(argv[1]);
    string src(argv[2]);

    const string FMT_FG_GREEN  = "\e[32m";
    const string FMT_UNDERLINE = "\e[4m";
    const string FMT_BOLD      = "\e[1m";
    const string FMT_RESET     = "\e[0m";
    const string CURRENT_FG_COLOR = FMT_FG_GREEN + FMT_UNDERLINE;
       
    cout << "\n" << FMT_BOLD << "regx" << FMT_RESET << " " 
         << FMT_UNDERLINE << "PATTERN" << FMT_RESET << " " 
         << FMT_UNDERLINE << "INPUT"   << FMT_RESET << "\n\n";

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
                
        int pos = match.position() + (idx * (CURRENT_FG_COLOR.length() + FMT_RESET.length()));
        int len = match.length();

        // set bash green start postion
        bash_str.insert(pos, CURRENT_FG_COLOR);

        // reset bash color position
        pos = pos + CURRENT_FG_COLOR.length() + len;
        bash_str.insert(pos, FMT_RESET);
       
        ++idx;
    }

    cout << "\nFound " << std::distance(begin, end) << " matches:\n";
    cout << bash_str << "\n\n";
}