#include <iostream>
#include <string>
#include <regex>
//#include <iterator>

using namespace std;

void replace_all(string& s, const string& sub_str, const string& replace_str);

int main(int argc, char* argv[]) 
{
    if(argc != 3)
        return 0;

    string exp = "\\<([A-z]+[A-z0-9]*)\\>";
    string pattern_str(argv[1]);
    string input_str(argv[2]);

    // cout << "regx [OPTIONS] PATTERN [FILE...]\n";
    // cout << "pattern: " << "\"" << exp << "\"" << " -> " 
    //         << "input: " << "\"" << src << "\"" << endl;

    replace_all(pattern_str, ".", "\\.");
    std::regex e(exp);
    
    std::smatch sm1;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match (pattern_str,sm1,e);

    string rep_str = std::regex_replace(pattern_str, e, "([A-z0-9\\. _-]*)");

    // std::regex rep(rep_str);
    // std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    // std::regex_match (rep_str, sm, rep);

    //TESTING
    // string s("abcxxxabcxxx");
    // std::regex ep("abc");
    // std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    
    // std::regex_match (s, sm, ep);
    // std::string s ("subject");
    // std::regex e1 ("(sub)(.*)");

    std::string s (input_str);
    //std::regex e1 ("([A-z0-9\\. _-]*)\\. ([A-z0-9\\. _-]*)-([A-z0-9\\. _-]*)\\.([A-z0-9\\. _-]*)");
    std::regex e1 (rep_str);

    std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
    std::regex_match (s,sm,e1);
    //std::cout << "string object with " << sm.size() << " matches\n";


    //std::cout << sm.str(0) << std::endl;
    // std::cout << sm.str(1) << std::endl;
    // std::cout << sm.str(2) << std::endl;
    // std::cout << sm.str(3) << std::endl;
    // std::cout << sm.str(4) << std::endl;
    //std::cout << "sm size=" << sm.size() << std::endl;

    // output tag values
    int len = sm.size();
    for(int i = 1; i < len; ++i)
    {
        std:cout << sm.str(i) << std::endl;
    }


    //std::cout << map.str(1) << "=" << tag_map[match.str(1)] << idx << std::endl;

    // cout << src << "\n";
    // cout << rep_str << "\n";
}

void replace_all(string& s, const string& sub_str, const string& replace_str)
{
    size_t pos = 0;
    size_t len = s.length();
   
    pos = s.find(sub_str, pos);
    while(pos < len)
    {
        s.replace(pos, sub_str.length(), replace_str);
        pos += replace_str.length();
        pos = s.find(sub_str, pos);
    }
}

// ./create_map "<track>. <artist>-<album>-<title>.<type>" "10. The Rolling Stones-Exile On Main St-Brown Sugar.mp3"
