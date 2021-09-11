#include <iostream>

using namespace std;

int tab[5001][5001] = {0};
string s1, s2;
int main (){
    ios_base::sync_with_stdio(0);

    int n1, n2, i, j;
    cin >> s1 >> s2;
    n1 = s1.size();
    n2 = s2.size();

    for(i = 0; i <= n1; ++i){
        for(j = 0; j <= n2; ++j){
            if(i == 0 || j == 0)
                tab[i][j] = 0;
            else{
                tab[i][j] = max(tab[i-1][j], tab[i][j-1]);
                if(s1[i-1] == s2[j-1])
                    tab[i][j] = max(tab[i][j], tab[i-1][j-1]+1);
            }
        }
    }

    cout << tab[n1][n2] << "\n";

    return 0;
}

#include <iostream>
int tab[5001][5001] = {0};
std::string s1, s2;
int main (){
    std::cin >> s1 >> s2;
    int n1 = s1.size(), n2 = s2.size(), i, j;
    for(i = 0; i <= n1; ++i)
        for(j = 0; j <= n2; ++j)
            tab[i][j] = (i == 0 || j == 0) ? 0 : std::max(std::max(tab[i-1][j], tab[i][j-1]), s1[i-1] == s2[j-1] ? tab[i-1][j-1]+1 : 0);
    std::cout << tab[n1][n2] << "\n";
    return 0;
}