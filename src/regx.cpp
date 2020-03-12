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

    std::string FG_GREEN = "\e[32m";
    std::string UNDERLINE = "\e[4m";
    std::string BOLD = "\e[1m";
    std::string RESET_FORMAT = "\e[0m";
    std::string CURRENT_FG_COLOR = FG_GREEN + UNDERLINE;
       
    //cout << "\nregx [OPTIONS] PATTERN INPUT\n";
    cout << "\n" << BOLD << "regx" << RESET_FORMAT << " " 
         << UNDERLINE << "PATTERN" << RESET_FORMAT << " " 
         << UNDERLINE << "INPUT"   << RESET_FORMAT << "\n";

    cout << "pattern: " << "\"" << exp << "\"" << " -> " 
            << "input: " << "\"" << src << "\"" << endl;

    std::regex tags(exp);
    auto begin = std::sregex_iterator(src.begin(), src.end(), tags);
    auto end = std::sregex_iterator();
    
    std::cout << "\nFound "
        << std::distance(begin, end)
        << " matches:\n";

    int idx = 0;
    string bash_str = src;
    for (std::sregex_iterator i = begin; i != end; ++i)
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

    cout << bash_str << "\n\n";
}