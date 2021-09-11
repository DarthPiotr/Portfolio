#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <queue>

using namespace std;


int dp[50][50][50][50];
short ssum, n, fsum;
short ftab[4], stab[4];

int main() {

    ios_base::sync_with_stdio(0);
    short t, i, j, k, sum, res, tmp;
    short tab[4], ttab[4];
    cin >> t;
    queue<short> Q;

    while (t--) {
        ssum = fsum = 0;
        for (k = 0; k < 4; k++)
            stab[k] = ftab[k] = tab[k] = ttab[k] = 0;
        memset(dp, -1, sizeof(dp));
        queue<short>().swap(Q);

        cin >> n;
        for (i = 0; i < n; i++) {
            cin >> stab[i];
            ssum += stab[i];
        }
        for (i = 0; i < n; i++) {
            cin >> ftab[i];
            fsum += ftab[i];
        }

        dp[stab[0]][stab[1]][stab[2]][stab[3]] = 0;
        for (k = 0; k < n; k++)
            Q.push(stab[k]);

        res = -1;
        while (!Q.empty()) {

            sum = 0;
            for (k = 0; k < n; k++) {
                tab[k] = Q.front();
                sum += tab[k];
                Q.pop();
            }

            if (tab[0] == ftab[0] &&
                tab[1] == ftab[1] &&
                tab[2] == ftab[2] &&
                tab[3] == ftab[3]) {
                res = dp[tab[0]][tab[1]][tab[2]][tab[3]];
                break;
            }
            //////////////////////////////////////////////////
            for (i = 0; i < n; i++) { // for each position
                if (tab[i] == 0) continue; // dont try pouring from empty

                for (j = 0; j < n; j++) { // where to pour it to 
                    if (i == j) { // if same, spill out
                        copy(tab, tab + n, ttab);
                        ttab[j] = 0;
                        if(sum-tab[j] >= fsum){
                            if (dp[ttab[0]][ttab[1]][ttab[2]][ttab[3]] == -1) {
                                dp[ttab[0]][ttab[1]][ttab[2]][ttab[3]] = dp[tab[0]][tab[1]][tab[2]][tab[3]]+1;
                                for (k = 0; k < n; k++)
                                    Q.push(ttab[k]);
                            }
                        }
                    }
                    else { // trying other
                        if (tab[j] == stab[j]) continue; // dont try filling full one
                        copy(tab, tab + n, ttab);
                        tmp = min((short)(stab[j] - tab[j]), tab[i]);
                        ttab[i] -= tmp;
                        ttab[j] += tmp;
                        if (dp[ttab[0]][ttab[1]][ttab[2]][ttab[3]] == -1) {
                            dp[ttab[0]][ttab[1]][ttab[2]][ttab[3]] = dp[tab[0]][tab[1]][tab[2]][tab[3]] + 1;
                            for (k = 0; k < n; k++)
                                Q.push(ttab[k]);
                        }
                    }
                }
            }
            /////////////////////////////////////////////////
        }
        if(res == -1)
            cout << "NO\n";
        else
            cout << res << "\n";
    }

    return 0;
}