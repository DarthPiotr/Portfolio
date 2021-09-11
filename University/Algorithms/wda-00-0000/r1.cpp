#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

long long** tab;
bool* exist;
int n;

bool sorting_via_columns(long long* a, long long* b)
{
    int i = 0;
    while(a[i] == b[i] && i < 2)
    {
        i++;
    }
    if (a[i] < b[i]) return true;
    return false;
}

void show(){
    cout << "\nTab:\n";
    for(int xd = 0; xd < n; xd++){
        cout << setw(3) << tab[xd][0] << setw(4) << tab[xd][1] << ", ex? : " << exist[xd] << "\n";
    }
    cout << "---\n";
}

int main ()
{
    int t, i, j;
    long long solution;
    cin >> t;
    while (t--)
    {
        solution = 0;
        cin >> n;
        tab = new long long* [n];
        exist = new bool [n];
        for(i = 0; i < n; i++)
        {
            exist[i] = 1;
        }
        for(i = 0; i < n; i++)
        {
            tab[i] = new long long [2];
            for(j = 0; j < 2; j++)
            {
                cin >> tab[i][j];
            }
        }
        sort(tab, tab + n, sorting_via_columns);

        //cout << "Before exist:\n";
        //show();

        for(i = 0; i < n - 1; i++)
        {
            if(tab[i][0] == tab[i+1][0])
            {
                exist[i] = 0;
            }
        }

        //cout << "After exist:\n";
        //show();

        for(i = 0; i < n - 1; i++)
        {
            cout << "Checking i=" << i << "\n";
            if(exist[i] == 1)
            {
                for(j = i + 1; j < n; j++)
                {
                    cout << "inner for  >>>>>>  Checking j=" << j << "\n";
                    if(exist[j] == 1)
                    {
                        if(tab[i][1] >= tab[j][0])
                        {
                            exist[j] = 0;
                            if(tab[i][1] <= tab[j][1])
                            {
                                tab[i][1] = tab[j][1];
                            }
                        }
                    }
                    /*if(tab[j][0] > tab[i][1] || j == n-1){
                        i = j-1;
                        break;
                    }*/
                }

                cout << "Finished inner for; new i=" << i << ", j=" << j << "\n";
                show();
            }
        }

        for (i = 0; i < n; i++)
        {
            if(exist[i] == 1)
            {
                solution += tab[i][1] - tab[i][0] + 1;
            }
        }

        cout << solution << "\n";

        for (i = 0; i < n; i++)
        {
            delete [] tab[i];
        }
        delete [] tab;

    }

return 0;
}