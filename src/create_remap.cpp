#include <iostream>
#include <string>
#include <regex>
#include <map>

using namespace std;

const string FMT_FG_GREEN  = "\e[32m";
const string FMT_UNDERLINE = "\e[4m";
const string FMT_BOLD      = "\e[1m";
const string FMT_RESET     = "\e[0m";
// sets allowed pattern for tag names
const string TAG_MATCH_EXP_STR = R"(\<([A-z]+[A-z0-9]*)\>)";
// regx special chars = ^ $ \ . * + ? ( ) [ ] { } | :
const string SPECIAL_CHARS_STR = R"([A-z0-9 \^\$\.\*\+\:\'\[\]\{\}\|;,@#_-])";
const regex TAG_EXP(TAG_MATCH_EXP_STR);

void replace_all(string& s, const string& sub_str, const string& replace_str);
map<string, string>& create_map(string& pattern, const string& s, map<string, string>& map);
//map<string, string>& create_map(const string& pattern, const string& s, map<string, string>& map);
string& create_formated_output(const string& s, map<string, string>& map, string& formated_output);

int main(int argc, char* argv[]) 
{
     if(argc < 4)
            return 0;

    // if(0)
    // {
    //     cout << "\n" << FMT_BOLD << "create_remap" << FMT_RESET << " " 
    //         << FMT_UNDERLINE << "INPUT_FORMAT" << FMT_RESET << " "
    //         << FMT_UNDERLINE << "INPUT" << FMT_RESET << " "  
    //         << FMT_UNDERLINE << "OUTPUT_FORMAT" << FMT_RESET << "\n\n";
    // }

    if(argc < 5)
    {
        string input_pattern_str(argv[1]);
        string input_str(argv[2]);
        string output_pattern_str(argv[3]);

        map<string, string> tag_map;
        create_map(input_pattern_str, input_str, tag_map);
        string formated_output;

        create_formated_output(output_pattern_str, tag_map, formated_output);
        cout << formated_output << endl;
    }
    else
    {
        //TODO file option ...
        string opts(argv[1]);
        string input_pattern_str(argv[2]);
        string input_str(argv[3]);
        string output_pattern_str(argv[4]);

        map<string, string> tag_map;
        create_map(input_pattern_str, input_str, tag_map);
        string formated_output;

        if(opts != "-f")
            return 0;
       
        // open file iter
        create_formated_output(output_pattern_str, tag_map, formated_output);
        cout << formated_output << endl;
    }

    return 0;
}

map<string, string>& create_map(string& pattern, const string& s, map<string, string>& map)
{
    // create regx from pattern
    replace_all(pattern, ".", "\\.");
    const string REPLACE_EXP_STR 
        = "^" + regex_replace(pattern, TAG_EXP, "(" + SPECIAL_CHARS_STR + "*)" ) + "$";
    const regex REPLACE_EXP (REPLACE_EXP_STR);
    
    // create smatch
    smatch sm;    
    regex_match (s, sm, REPLACE_EXP);
    
    // iterate through tag matches and create map
    int idx = 1;
    auto begin = sregex_iterator(pattern.begin(), pattern.end(), TAG_EXP);
    auto end = sregex_iterator();
    
    for (sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
        map.insert(make_pair(match.str(1), sm.str(idx++)));
    }

    return map;
}

string& create_formated_output(const string& s, map<string, string>& map, string& formated_output)
{
    auto begin = sregex_iterator(s.begin(), s.end(), TAG_EXP);
    auto end = sregex_iterator();
    formated_output = s;
   
    int format_str_pos = 0;
    int format_str_end = 0;
    int output_str_pos = 0;
    int relative_pos = 0;

    for (sregex_iterator i = begin; i != end; ++i)
    {
        smatch match = *i;
        string tag_value = map[match.str(1)];
        
        // get current match position 
        format_str_pos = match.position();
        // set realtive to last end
        relative_pos = format_str_pos - format_str_end;
        output_str_pos += relative_pos;
        // set new end
        format_str_end = format_str_pos + match.length();
        // replace <tag> with tag value
        formated_output.replace(output_str_pos, match.length(), tag_value);
        // set pos to end of replace
        output_str_pos += tag_value.length(); 
    }

    return formated_output;
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
./create_remap "<track>. <artist>-<album>-<title>.<type>" "10. The Rolling Stones-Exile On Main Street-Brown Sugar.mp3" "<track>: <title>.<type"
./create_remap "<first> <last>:<phone> <sex>" "Alfred E. Numan:555-555-9696 M" "Sex : <sex>    Name :<last>, <first>    Phone : <phone>"
./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "/<artist>/<album>/<track>. <title>.<type>"

mkdir -p "$(./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "./<artist>/<album>/")" 
touch "$(./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "./<artist>/<album>/<track>. <title>.<type>")"
*/
