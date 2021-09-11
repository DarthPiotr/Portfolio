#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int t;
string s;
short len, tab[6100][6100];

int main() {

    ios_base::sync_with_stdio(0);

    short i, j;

    cin >> t;
    while (t--) {
        cin >> s;
        len = s.size();

        for (i = 0; i < len; i++) {
            for (j = 0; j < len; j++) {
                if (s[i] == s[len - j - 1]) {
                    tab[i][j] = (i > 0 && j > 0) ? tab[i - 1][j - 1] + 1 : 1;
                }
                else {
                    tab[i][j] = max(
                        i > 0 ? tab[i-1][j] : 0,
                        j > 0 ? tab[i][j-1] : 0
                    );
                }
            }
        }

        cout << len - tab[len - 1][len - 1] << "\n";
    }

    return 0;
}