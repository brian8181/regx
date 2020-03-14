#include <iostream>
#include <string>
#include <regex>
#include <map>

using namespace std;

void replace_all(string& s, const string& sub_str, const string& replace_str);

int main(int argc, char* argv[]) 
{
    if(argc != 3)
        return 0;

    string pattern_str(argv[1]);
    string input_str(argv[2]);

    const string FMT_FG_GREEN  = "\e[32m";
    const string FMT_UNDERLINE = "\e[4m";
    const string FMT_BOLD      = "\e[1m";
    const string FMT_RESET     = "\e[0m";

     cout << "\n" << FMT_BOLD << "create_map" << FMT_RESET << " " 
          << FMT_UNDERLINE << "PATTERN" << FMT_RESET << " " 
          << FMT_UNDERLINE << "INPUT"   << FMT_RESET << "\n\n";

    // sets allowed pattern for tag names
    const string TAG_MATCH_EXP_STR = R"(\<([A-z]+[A-z0-9]*)\>)";
    // regx special chars = ^ $ \ . * + ? ( ) [ ] { } | :
    const string SPECIAL_CHARS_STR = R"([A-z0-9 \^\$\.\*\+\:\'\[\]\{\}\|;,@#_-])";

    // create regx from pattern
    replace_all(pattern_str, ".", "\\.");
    const regex TAG_EXP(TAG_MATCH_EXP_STR);
    const string REPLACE_EXP_STR 
        = "^" + regex_replace(pattern_str, TAG_EXP, "(" + SPECIAL_CHARS_STR + "*)" ) + "$";
    const regex REPLACE_EXP (REPLACE_EXP_STR);
    
    // create smatch
    smatch sm;    
    regex_match (input_str, sm, REPLACE_EXP);
    
    // iterate through tag matches and create map
    int idx = 1;
    auto begin = sregex_iterator(pattern_str.begin(), pattern_str.end(), TAG_EXP);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
        map<string,string> tag_map;
        tag_map.insert(make_pair(match.str(1), sm.str(idx)));
      
        cout << FMT_BOLD + FMT_FG_GREEN << match.str(1) << FMT_RESET << " = " 
                  << tag_map[match.str(1)] << endl;
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

/*
USAGE:
./create_map "<track>. <artist>-<album>-<title>.<type>" "10. The Rolling Stones-Exile On Main Street-Brown Sugar.mp3"
./create_map "<track>: <artist>_<album>_<title>.<type>" "10: The Rolling Stones_Exile On Main Street_Brown Sugar.mp3"
./create_map "<test>" "ABCDEFGHIJKLMPNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+_-*^|:[]{}'"
*/