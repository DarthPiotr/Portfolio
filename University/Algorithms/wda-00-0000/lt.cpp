#include <iostream>
#include <iomanip>

using namespace std;

int MyHash(string key) {
    int sum = 0, len = key.size();
    for (int i = 0; i < len; i++) {
        sum += (int)key[i] * (i + 1);
    }
    return (19 * sum) % 101;
}

int YourHash (string s)
{
    int i, p = 0;
    for (i = 0; i < s.size(); i++)
    {
        p += (int)s[i] * (i + 1);
    }
    p = (p * 19) % 101;
    return p;
}

int main (){

    ios_base::sync_with_stdio(0);

    string a = "e";
    int yourh = YourHash(a), Hash2;
    int mineh = MyHash(a), index;

    cout << "Your |    My\n ";
    cout << yourh << " | " << mineh << "\n";

    for(int j = 0; j <= 19; j++)
    {
        Hash2 = (yourh + j * j + 23 * j) % 101;

        index = (mineh + j * j + 23 * j)%101;

        cout <<  setw(3) << Hash2 << " | " << setw(3) << index << "\n";
    }


    return 0;
}