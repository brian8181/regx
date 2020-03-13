#include <iostream>
#include <string>
#include <regex>
#include <map>
//#include <algorithm>

using namespace std;

void replace_all(string& s, const string& sub_str, const string& replace_str);

int main(int argc, char* argv[]) 
{
    if(argc != 3)
        return 0;

    // sets allowed pattern for tag names
    const string TAG_MATCH_EXP_STR = R"(\<([A-z]+[A-z0-9]*)\>)";
    // regx special chars = ^ $ \ . * + ? ( ) [ ] { } | :
    const string SPECIAL_CHARS_STR = "([A-z0-9 \\.\\*\\+\\:\\'\\[\\]\\{\\}\\|_-]*)";

    string pattern_str(argv[1]);
    string input_str(argv[2]);

    // output command format
    cout << "\ncreate_map [OPTIONS] PATTERN INPUT\n\n";
    cout << "pattern: " << "\"" << pattern_str << "\"" << "\n";
    cout << "input: " << "\"" << input_str << "\"" << "\n\n";

    // create regx from pattern
    replace_all(pattern_str, ".", "\\.");
    const std::regex TAG_EXP(TAG_MATCH_EXP_STR);
    const string REPLACE_EXP_STR = "^" + std::regex_replace(pattern_str, TAG_EXP, SPECIAL_CHARS_STR ) + "$";
    const std::regex REPLACE_EXP (REPLACE_EXP_STR);
    
    // create smatch
    std::smatch sm;    
    std::regex_match (input_str, sm, REPLACE_EXP);
    
    // iterate through tag matches and create map
    int idx = 1;
    auto begin = std::sregex_iterator(pattern_str.begin(), pattern_str.end(), TAG_EXP);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
        std::map<std::string,std::string> tag_map;
        tag_map.insert(std::make_pair(match.str(1), sm.str(idx)));
      
        std::cout << match.str(1) << " = " << tag_map[match.str(1)] << std::endl;
        ++idx;
    }
    
    cout << "\n";
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

// ./create_map "<track>. <artist>-<album>-<title>.<type>" "10. The Rolling Stones-Exile On Main Street-Brown Sugar.mp3"
// ./create_map "<track>: <artist>_<album>_<title>.<type>" "10: The Rolling Stones_Exile On Main Street_Brown Sugar.mp3"
