
// Zlozonosc O(n*m)

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct it{
    int v=0,w=0;
}T[1000];

int m, n, dp[1000][1000];
int main(){

    ios_base::sync_with_stdio(0);

    cin >> n >> m;

    cerr << "wczytano mn\n";

    for(int i = 1; i < n; i++){
        cin >> T[i].w >> T[i].v;
    }
    cerr << "wczytano\n";

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            
            if(i == 0 || j == 0){
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = dp[i-1][j];
                if(T[i].w <= j) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-T[i].w]+T[i].v);
                }
            }
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    cout << dp[n][m];

    return 0;
}