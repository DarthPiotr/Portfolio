#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

int dp[50][50][50][50];

short n, finsum;
short ftab[4], stab[4];
bool found = false;

void solve(short tab[4], int steps, short sum) {

    if (sum < finsum) return;

    /*if (tab == ftab) {
        found = true;
        return;
    }*/

    short ttab[4];
    if (dp[tab[0]][tab[1]][tab[2]][tab[3]] == -1 || steps < dp[tab[0]][tab[1]][tab[2]][tab[3]])
        dp[tab[0]][tab[1]][tab[2]][tab[3]] = steps;
    else return;

    for (short i = 0; i < n; i++) { // for each position
        if (tab[i] == 0) continue; // dont try pouring from empty

        for (short j = 0; j < n; j++) { // where to pour it to 
            if (i == j) { // if same, spill out
                copy(tab, tab + 4, ttab);

                ttab[j] = 0;
                solve(ttab, steps+1, sum - tab[j]);
            }
            else { // trying other
                if (tab[j] == stab[j]) continue; // dont try filling full one

                copy(tab, tab + 4, ttab);
                ttab[i] -= min((short)(stab[j] - tab[j]), tab[i]);
                ttab[j] += min((short)(stab[j] - tab[j]), tab[i]);

                solve(ttab, steps+1, sum);
            }
            //if (found) return;
        }
    }
}

int main() {

    ios_base::sync_with_stdio(0);
    short t, i, sum;
    int res;
    cin >> t;

    while (t--) {
        sum = finsum = 0;
        found = false;
        memset(dp, -1, sizeof(dp));
        memset(stab, 0, sizeof(stab));

        cin >> n;
        for (i = 0; i < n; i++) {
            cin >> stab[i];
            sum += stab[i];
        }
        for (i = 0; i < n; i++) {
            cin >> ftab[i];
            finsum += ftab[i];
        }

        solve(stab, 0, sum);
        res = dp[ftab[0]][ftab[1]][ftab[2]][ftab[3]];
        cout << (res == -1 ? "NO" : to_string(res)) << "\n";
    }


    return 0;
}