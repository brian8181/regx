#include <iostream>
#include <string>
#include <regex>
#include <map> 

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
        std::string UNDERLINE = "\e[4m";
        std::string RESET_FORMAT = "\e[0m";
        std::string CURRENT_FG_COLOR = FG_GREEN + UNDERLINE;
       
        smatch match = *i;

        std::string tag_name = "testing";
        
        std::map<std::string,std::string> tag_map;
        tag_map.insert(std::make_pair(match.str(1), "test"));
        // tag_map.insert(std::make_pair(match.str(1), "test2"));
        // tag_map.insert(std::make_pair(match.str(1), "test3"));

        std::cout << match.str(0) << std::endl;
        std::cout << match.str(1) << "=" << tag_map[match.str(1)] << idx << std::endl;
                     
        int pos = match.position() + (idx * (CURRENT_FG_COLOR.length() + RESET_FORMAT.length()));
        int len = match.length();
        // set bash green start postion
        bash_str.insert(pos, CURRENT_FG_COLOR);

        // reset bash color position
        pos = pos + CURRENT_FG_COLOR.length() + len;
        bash_str.insert(pos, RESET_FORMAT);
       
        ++idx;
    }

    cout << bash_str << "\n";
}

// string EscapeRegxChars(const string& s)
// {
//     size_t pos = bash_str.find(".");
//     bash_str.replace(pos, 1, "\\.");
// }