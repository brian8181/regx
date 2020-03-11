#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) 
{
    if(argc != 2)
        return 0;

    string exp = "\\<([A-z]+[A-z0-9]*)\\>";
    string src(argv[1]);

    cout << "regx [OPTIONS] PATTERN [FILE...]\n";
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
    string reg_exp;

    for (std::sregex_iterator i = begin; i != end; ++i)
    { 
        std::string FG_GREEN = "\e[32m";
        std::string UNDERLINE = "\e[4m";
        std::string RESET_FORMAT = "\e[0m";
        std::string CURRENT_FG_COLOR = FG_GREEN + UNDERLINE;
       
        smatch match = *i;

        std::cout << match.str() << std::endl;

        size_t pos = bash_str.find(".");
        bash_str.replace(pos, 1, "\\.");
        bash_str.replace(match.position(), match.length(), "(.*)");
        
        break;


        // int pos = match.position() + (idx * (CURRENT_FG_COLOR.length() + RESET_FORMAT.length()));
        // int len = match.length();
        // // set bash green start postion
        // bash_str.insert(pos, CURRENT_FG_COLOR);

        // // reset bash color position
        // pos = pos + CURRENT_FG_COLOR.length() + len;
        // bash_str.insert(pos, RESET_FORMAT);
       
        //++idx;
    }

    cout << bash_str << "\n";
}