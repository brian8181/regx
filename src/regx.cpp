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
    for (std::sregex_iterator i = begin; i != end; ++i)
    {
        std::string FG_GREEN = "\e[32m";
        std::string RESET_FORMAT = "\e[0m";
        std::string UNDERLINE = "\e[4m";
       
        smatch match = *i;
                
        int pos = match.position() + (idx * (FG_GREEN.length() + RESET_FORMAT.length()));
        int len = match.length();

        // set bash green start postion
        bash_str.insert(pos, FG_GREEN);

        // reset bash color position
        pos = pos + FG_GREEN.length() + len;
        bash_str.insert(pos, RESET_FORMAT);
       
        ++idx;
    }

    cout << bash_str << "\n";
}