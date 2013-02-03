#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

struct pos
{
    int row = 0;
    int col = 0;
};

namespace
{
    const int nof_rows = 6;
    const int row_length = 5;
}

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

void findPosition(std::vector< std::vector<char> >& legend, pos& letter_pos, char c)
{
    for (int row = 0; row < nof_rows; ++row)
    {
        for (int col = 0; col < row_length; ++col)
        {
            if (legend.at(row).at(col) == c)
            {
                letter_pos.row = row;
                letter_pos.col = col;
                return;
            }
        }
    }
}

string encode(std::vector< std::vector<char> >& legend, const std::string& str)
{
    pos char1_pos;
    pos char2_pos;
    string encoded_pair;

    findPosition(legend, char1_pos, str[0]);
    findPosition(legend, char2_pos, str[1]);

    int delta_rows = max(char1_pos.row, char2_pos.row) - min(char1_pos.row, char2_pos.row);
    int delta_cols = max(char1_pos.col, char2_pos.col) - min(char1_pos.col, char2_pos.col);

    stringstream ss;

    if (delta_rows == 0)
    {
        // På samma rad
        if (char1_pos.col + 1 >= row_length)
            ss << legend.at(char1_pos.row).at(0);
        else
            ss << legend.at(char1_pos.row).at(char1_pos.col + 1);

        if (char2_pos.col + 1 >= row_length)
            ss << legend.at(char2_pos.row).at(0);
        else
            ss << legend.at(char2_pos.row).at(char2_pos.col + 1);
    }
    else if (delta_cols == 0)
    {
        // I samma kolumn
        if (char1_pos.row + 1 >= nof_rows)
            ss << legend.at(0).at(char1_pos.col);
        else
            ss << legend.at(char1_pos.row + 1).at(char1_pos.col);

        if (char2_pos.row + 1 >= nof_rows)
            ss << legend.at(0).at(char2_pos.col);
        else
            ss << legend.at(char2_pos.row + 1).at(char2_pos.col);
    }
    else
    {
        // Rektangel
        if (char1_pos.col - char2_pos.col < 0)
        {
            ss << legend.at(char1_pos.row).at(char1_pos.col + delta_cols);
            ss << legend.at(char2_pos.row).at(char2_pos.col - delta_cols);
        }
        else
        {
            ss << legend.at(char1_pos.row).at(char1_pos.col - delta_cols);
            ss << legend.at(char2_pos.row).at(char2_pos.col + delta_cols);
        }
    }

    ss >> encoded_pair;
    return encoded_pair;
}

int main(int argc, char* argv[])
{
    cout << "Enter key: ";

    string key;
    cin >> key;

    vector< vector<char> > legend;
    string alphabet = "abcdefghijklmnopqrstuvwxyz\x86\x84\x94 ";

    for (int i = 0; i < key.length(); ++i)
        removeAllButFirst(key, key[i]);

    // Ordna om alfabetet
    for (int i = 0; i < key.length(); ++i)
        bringToFront(alphabet, key[key.length() - i - 1]);

    // Fyll listan

    for (int row = 0; row < nof_rows; ++row)
    {
        vector<char> temp;

        for (int col = 0; col < row_length; ++col)
        {
            // Lägg i legend
            temp.push_back(alphabet.at(0));
            // Ta bort ur listan
            alphabet.erase(0, 1);
        }

        legend.push_back(temp);
    }

    for (int row = 0; row < nof_rows; ++row)
    {
        for (int col = 0; col < row_length; ++col)
        {
            cout << legend[row][col] << " ";
        }

        cout << endl;
    }

    string message;
    string encoded_message;

    cin >> message;

    if (message.length() % 2 != 0)
        message.append(" ");

    for (int i = 0; i < message.length(); i += 2)
    {
        encoded_message.append(encode(legend, message.substr(i,2)));
    }

    cout << "Krypterat meddelande: " << encoded_message << endl;

    return 0;
}


