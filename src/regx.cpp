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
         << "input: " << "\"" << src << "\"" << "\n\n";

    int idx = 0;
    string bash_str = src;
    regex src_epx(exp);
    auto begin = sregex_iterator(src.begin(), src.end(), src_epx);
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

        cout << idx << ": " << src.substr(match.position(), match.length()) << endl; 
       
        ++idx;
    }

    cout << "\nFound " << std::distance(begin, end) << " matches:\n";
    cout << bash_str << "\n\n";
}

/*

#MATCH
./regx "a\\\\b" "a\\b"
./regx "a\\*b" "a*b"
./regx "a\\=b" "a=b"
./regx "a\\+b" "a+b"
./regx "a~b" "a~b"
./regx "a~b" "a~b"
./regx 'a`b' 'a`b'
./regx 'a-b' 'a-b'
./regx "a-b" "a-b"
./regx "a#b" "a#b"
./regx "a@b" "a@b"
./regx "a\\$" "a$"
./regx "a&b" "a&b"
./regx "a\\&b" "a&b"
./regx "a\\(b" "a(b"
./regx "a\\)b" "a)b"
./regx "a\(b\)c" "a(b)c"
./regx "a\[b\]c" "a[b]c"
./regx "a\{b\}c" "a{b}c"

# STRANGE BOTH MATCH
./regx 'a"b' 'a"b'
./regx 'a\"b' 'a"b'

#NO MATCH
#./regx "a\\!b" "a!b"
# ./regx "a`b" "a`b"
# ./regx "a\\$b" "a$b"

# GREEDY TESTING
./regx "a.*?b" "axbb" // MATCH = axb

# TAGS
## OK
./regx "\\<([A-z]+[A-z0-9]*)\\>" "<tag1> <tag2>"
./regx "\\<([A-z]+[A-z0-9]*)\\>" "<tag1> <tag2><tag3>"

# FUNNY
./regx "\\<([A-z]+[A-z0-9\\<\\>]*?)+\\>" "<tag1<tag4>> <tag2><tag3>"

# WORKS WITH WORD BOUNDRAY \b
./regx "\\<\b([A-z]+[A-z0-9\\<\\>]*?)+\b\\>" "<tag1>. <tag2><tag3>*<tag5>&<tag6>^<tag7>|<tag8>"

*/