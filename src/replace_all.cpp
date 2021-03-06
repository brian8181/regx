#include <iostream>
#include <string>
#include <regex>

using namespace std;

void replace_all(string& s, const string& sub_str, const string& replace_str);

int main(int argc, char* argv[]) 
{
    if(argc != 4)
        return 0;

    string src(argv[1]);
    string sub_str(argv[2]);
    string replace_str(argv[3]);

    replace_all(src, sub_str, replace_str);

    cout << src << endl;
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