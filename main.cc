#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

void removeAllButFirst(std::string& str, char c)
{
    size_t first_pos = str.find_first_of(c);
    size_t pos = str.find_first_of(c, first_pos + 1);

    while (pos != string::npos)
    {
        str.erase(pos, 1);
        pos = str.find_first_of(c, first_pos + 1);
    }
}

void bringToFront(std::string& str, char c)
{
    size_t pos = str.find_first_of(c);

    if (pos == string::npos || pos == 0)
        return;

    stringstream ss;
    string s;
    ss << c;
    ss >> s;

    str.erase(pos, 1);
    str.insert(0, s);
}

int main(int argc, char* argv[])
{
    cout << "Enter key: ";

    string key;
    cin >> key;

    vector< vector<char> > legend;
    string alphabet = "abcdefghijklmnopqrstuvxyz\x86\x84\x94 ";

    for (int i = 0; i < key.length(); ++i)
        removeAllButFirst(key, key[i]);

    // Ordna om alfabetet
    for (int i = 0; i < key.length(); ++i)
        bringToFront(alphabet, key[key.length() - i - 1]);

    return 0;
}


