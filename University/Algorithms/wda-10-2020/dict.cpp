#include <iostream>
#include <string>
#include <set>

using namespace std;

set<string> dict;

int main() {

    ios_base::sync_with_stdio(0);

    int n, k, i, len, tlen;
    string tmp;
    bool found;
    cin >> n;
    while (n--) {
        cin >> tmp;
        dict.insert(tmp);
    }
    cin >> k;
    n = k;
    while (k--) {
        cin >> tmp;
        tlen = tmp.size();
        cout << "Case #" << n - k << ":\n";
        found = false;
        for (const string& s : dict) {
            if (tmp[0] < s[0]) break;

            len = s.size();
            if (tmp == s || len < tlen) continue;

            for (i = 0; i < tlen; i++) {
                if (tmp[i] != s[i]) goto end;
            }
            cout << s << "\n";
            found = true;

        end:
            continue;
        }
        if (!found) cout << "No match.\n";
    }

    return 0;
}