#include <iostream>
#include <string>

using namespace std;

int main (){

    ios_base::sync_with_stdio(0);

    string s = "1234567890987654321", s1, s2;
    int len = s.size();
    for(int i = 0; i <len; i++){
        s1 = s.substr(0, i) + "A" + s.substr(i);
        for(int j = 0; j <s1.size(); j++){
            s2 = s1.substr(0, j) + "B" + s1.substr(j);
            cout << s2 << "\n";
        }
    }

    return 0;
}