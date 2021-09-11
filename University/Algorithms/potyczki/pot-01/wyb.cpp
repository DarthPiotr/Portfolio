#include <iostream>

using namespace std;

short n;
string zad;
short tab[5][3] = { 0 };

int main() {

    ios_base::sync_with_stdio(0);

    cin >> n;
    while (n--) {
        cin >> zad;
        tab[zad[0] - '1'][zad[1] - 'A']++;
    }

    if (tab[4][0] < 2 || tab[4][1] < 2 || tab[4][2] < 2) {
        cout << "NIE";
        return 0;
    }

    for (n = 0; n < 5; n++) {
        if (n < 4 && (tab[n][0] < 1 || tab[n][1] < 1 || tab[n][2] < 1)) {
            cout << "NIE";
            return 0;
        }
    }

    cout << "TAK";
    return 0;
}