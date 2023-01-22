#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


using namespace std;

int main()
{
    int n = 36;
    string str;
    stringstream ss;
    ss << setw(4) << setfill('0') << n;
    ss >> str;
    cout << str << endl;

    string num_str = "0000";
    string s = "abcdefghijklmn";
    int num = 0;
    stringstream sss;
    sss << num_str;
    sss >> num;
    cout << num << endl;
    cout << s.substr(1, num) << endl;;
}
