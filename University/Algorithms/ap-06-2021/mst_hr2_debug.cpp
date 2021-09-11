#include <iostream>

using namespace std;

typedef long long li;

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        li n, m, mst;
        cin >> n >> m >> mst;
        li pelny = (n - 1) * (n - 2) / 2;

        cout << n << " " << m << " " << mst << " " << pelny << " ";


        if (m <= pelny) {
            cout << "- - - - - N__ - " << mst + m - (n - 1) << endl;
        } else {

            li kra_d_ost = m - pelny;
            li wag_d_ost = mst - (n - 2);
            li res = pelny + wag_d_ost * kra_d_ost;

            cout << kra_d_ost << " " << wag_d_ost << " " << res << " " << kra_d_ost*(n-2) << " " << pelny - kra_d_ost * (n - 2) << " Y";

            if (pelny < kra_d_ost * (n - 2)) {
                cout << "+";
                li fulls = (wag_d_ost - 1) / (n - 1);
                res += (pelny - kra_d_ost * (n - 2)) * fulls;
                wag_d_ost -= (n - 2) * fulls;
                if (wag_d_ost - 1 >= fulls + 2) {
                    cout << "*";
                    li rem = (wag_d_ost - 1) - (fulls + 2) + 1;
                    li delta = rem * (n - 1) - rem * (rem + 1) / 2 - kra_d_ost * rem;
                    if (delta < 0){
                        cout << "^ " << fulls << " ";
                        res += delta;
                    }
                    else cout << "_ " << fulls << " ";
                }
                else {
                    cout << "__ " << fulls << " ";
                }
            }
            else{
                cout << "__ - ";
            }

            cout << res << endl;
        }
    }
    return 0;
}