#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <fstream>

using namespace std;

// shell color constants
const string FMT_FG_GREEN  = "\e[32m"; 
const string FMT_UNDERLINE = "\e[4m";
const string FMT_BOLD      = "\e[1m";
const string FMT_RESET     = "\e[0m";

// sets allowed pattern for tag names
const string TAG_MATCH_EXP_STR = R"(\<([A-z]+[A-z0-9]*)\>)";
// regx special chars = ^ $ \ . * + ? ( ) [ ] { } | :
const string SPECIAL_CHARS_STR = R"([A-z0-9 \^\$\.\*\+\:\'\[\]\{\}\|;,@#_-])";
const regex TAG_EXP(TAG_MATCH_EXP_STR);

// functions
void replace_all(string& s, const string& sub_str, const string& replace_str);
map<string, string>& create_map(const string& pattern, const string& s, map<string, string>& map);
string& create_formated_output(const string& s, map<string, string>& map, string& formated_output);

// TODO: order args
/*

create_remap [opts] INPUT_PATTERN OUTPUT_PATTERN [INPUT ... ]

*/

int main(int argc, char* argv[]) 
{
     if(argc < 4)
            return -1; //args error

    string input_pattern_str;
    string input_str;
    string output_pattern_str;

    if(0)
    {
        input_pattern_str = argv[1];
        input_str = argv[2];
        output_pattern_str = argv[3];

        map<string, string> tag_map;
        create_map(input_pattern_str, input_str, tag_map);
        string formated_out;

        create_formated_output(output_pattern_str, tag_map, formated_out);
        cout << formated_out << endl;
    }
    else
    {
        string opts( argv[1] );
        input_pattern_str = argv[2];
        input_str = argv[3];
        output_pattern_str = argv[4];
 
        if(opts != "-f")
            return -1; //args error
        
        // iter all lines
        map<string, string> tag_map;
        string formated_out;
        std::ifstream file(input_str);

        while (std::getline(file, input_str))
        { 
            tag_map.clear();
            create_map(input_pattern_str, input_str, tag_map);
            // open file iter
            formated_out;
            create_formated_output(output_pattern_str, tag_map, formated_out);
            cout << formated_out << endl;
        }
    }
    return 0;
}

map<string, string>& create_map(const string& pattern, const string& s, map<string, string>& map)
{
    // create copy of pattern
    string pattern_cpy = pattern;
    // create regx from pattern
    replace_all(pattern_cpy, ".", "\\.");
    const string REPLACE_EXP_STR 
        = "^" + regex_replace(pattern_cpy, TAG_EXP, "(" + SPECIAL_CHARS_STR + "*)" ) + "$";
    const regex REPLACE_EXP (REPLACE_EXP_STR);
    
    // create smatch
    smatch sm;    
    regex_match (s, sm, REPLACE_EXP);
    
    // iterate through tag matches and create map
    int idx = 1;
    auto begin = sregex_iterator(pattern_cpy.begin(), pattern_cpy.end(), TAG_EXP);
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
    formated_output = s; // copy s
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
./create_remap "<track>. <artist>-<album>-<title>.<type>" "10. The Rolling Stones-Exile On Main Street-Brown Sugar.mp3" "<track>: <title>.<type>"
./create_remap "<first> <last>:<phone> <sex>" "Alfred E. Numan:555-555-9696 M" "Sex : <sex>    Name :<last>, <first>    Phone : <phone>"
./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "/<artist>/<album>/<track>. <title>.<type>"
./create_remap "/<artist>/<album>" "/Bob Dylan/Highway 61 Revisited" "<artist>-<album>"
./create_remap "/<artist>/<album>/<track>. <title>.<type>" "/Bob Dylan/1965 - Highway 61 Revisited/01. Like a Rolling Stone.mp3" "<track>: <artist>-<album>-<title>.<type>"

-FILE INPUT:
./create_remap -f "/<artist>/<album>/<track>. <title>.<type>" "remap_test_cases.txt" "<track>: <artist>-<album>-<title>.<type>"
./create_remap -f "<track>: <artist>-<album>-<title>.<type>" "remap_test_case_files_to_dirs.txt" "/<artist>/<album>/<track>. <title>.<type>"

-TEST CREATING COMMANDS
mkdir -p "$(./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "./<artist>/<album>/")" 
touch "$(./create_remap "<track>. <artist> - <album> - <title>.<type>"  "10. The Rolling Stones - Exile On Main Street - Brown Sugar.mp3"  "./<artist>/<album>/<track>. <title>.<type>")"

-CREATE COPY COMMAND
./create_remap -f "/<artist>/<album>/<track>. <title>.<type>" \
"remap_test_cases.txt" \
"mkdir -p \"/home/brian/tmp/<artist>/<album>/\" & cp \"/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<track>. <title>.<type>\" \"/home/brian/tmp/<artist>/<album>/<track>: <artist>-<album>-<title>.<type>\""\
> copy.sh

--RUN IT?
#chmod +x copy.sh
#./copy.sh

*/
