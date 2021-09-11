#include <iostream>

using namespace std;

int k, l;
string s = "", s2;

string neighbors(char c) {
    string str = "";
    int spaces = max(0, c-1-'0');
    while (spaces--) str += "_";


    if (c - 1 >= '0') str += c - 1;
    str += c;
    if (c + 1 <= '0' + k) str += c + 1;
    return str;
}

int main() {

    ios_base::sync_with_stdio(0);

    cout << "k: ";
    cin >> k;
    cout << "L: ";
    cin >> l;
    for (int i = 0; i <= k; i++)
        s += '0' + i;

    cout << "\n\n";
    for (int i = 0; i <= l; i++) {
        cout << "L= " << i << "\n";
        cout << s << "\n";
        cout << "------------\n\n";

        s2 = "";
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == '-') {
                s2 += "---\n";
                j += 2;
            }
            else if (s[j] != '\n' && s[j] != '_') {
                s2 += neighbors(s[j]);
                if (i == 1)
                    s2 += "\n---";
                s2 += "\n";
            }
        }
        s = s2;
    }

    return 0;
}