#include <iostream>
#include <string>

using namespace std;

string tab[101];
short s, t, n;

int Hash(string key) {
    int sum = 0, len = key.size();
    for (int i = 0; i < len; i++) {
        sum += (int)key[i] * (i + 1);
    }
    return (19 * sum) % 101;
}

void insert(string key) {
    int hash = Hash(key);
    int index, indexok = -1;
    for (int i = 0; i < 20; i++) {
        index = (hash + i * i + 23 * i)%101;
        if (tab[index] == key)
            return;
        if (indexok < 0 && tab[index] == "") {
            indexok = index;
        }
    }
    if(indexok >= 0) {
        tab[indexok] = key;
        s++;
    }
}

void remove(string key) {
    int hash = Hash(key);
    int index;
    for (int i = 0; i < 20; i++) {
        index = (hash + i * i + 23 * i) % 101;
        if (tab[index] == key) {
            tab[index] = "";
            s--;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    short i, j;
    string tmp;
    
    cin >> t;

    for (i = 0; i < t; i++) {
        cin >> n;

        s = 0;
        for (j = 0; j < 101; j++) {
            tab[j] = "";
        }

        for (j = 0; j < n; j++) {
            cin >> tmp;
            if (tmp[0] == 'A')
                insert(tmp.substr(4, tmp.size() - 4));
            else
                remove(tmp.substr(4, tmp.size() - 4));
        }

        cout << s << "\n";
        for (j = 0; j < 101; j++) {
            if (tab[j] != "")
                cout << j << ":" << tab[j] << "\n";
        } 
    }

    return 0;
}