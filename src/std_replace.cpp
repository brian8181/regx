//C++ STL program to demonstrate use of
//std::replace() function
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    //vector
    vector<int> v{ 10, 20, 10, 20, 10, 30, 40, 50, 60, 70 };

    //printing vector elements
    cout << "before replacing, v: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;

    //replacing 10 with 99
    replace(v.begin(), v.end(), 10, 99);

    //printing vector elements
    cout << "after replacing, v: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;

    return 0;
}