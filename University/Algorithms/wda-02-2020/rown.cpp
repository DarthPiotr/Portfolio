#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main(){

    string s;
    int z, i, j, sz;
    char c;

    long long numbers, xes;
    long long currentNum;
    bool neg, otherside;
    double res;

    cin >> z;

    for(i = 0; i < z; i++){
        cin >> s;
        sz = s.size();

        numbers = 0;
        xes = 0;

        currentNum = 0;
        neg = false;
        otherside = false;

        if(s.find("-=") != string::npos){
                cout << "NO\n";
                continue;
        }

        for(j = 0; j < sz; j++){
            c = s[j];

            // cyfra
            if(c >= '0' && c <= '9'){
                currentNum = 10*currentNum + ((int)c - (int)'0');
            }
            else if(c == 'x'){
                if((j > 0 && (s[j-1] == '+' || s[j-1] == '-' || s[j-1] == '=')) || j == 0)
                    currentNum = 1;

                if(neg)
                    currentNum = -currentNum;
                if(otherside)
                    currentNum = -currentNum;

                xes += currentNum;

                currentNum = 0;
                neg = false;
            }
            else if(c == '='){
                if(neg)
                    currentNum = -currentNum;
                if(otherside)
                    currentNum = -currentNum;

                numbers += currentNum;

                currentNum = 0;
                neg = false;

                otherside = true;
            }
            else if(c == '+'){
                if(neg)
                    currentNum = -currentNum;
                if(otherside)
                    currentNum = -currentNum;

                numbers += currentNum;

                currentNum = 0;
                neg = false;
            }
            else if(c == '-'){
                if(neg)
                    currentNum = -currentNum;
                if(otherside)
                    currentNum = -currentNum;

                numbers += currentNum;

                neg = true;
                currentNum = 0;
            }
        }

        if(c != 'x'){
            if(neg)
                currentNum = -currentNum;
            if(otherside)
                currentNum = -currentNum;
            numbers += currentNum;
        }

        if(xes == 0)
            cout << "NO\n";
        else{
            res = -(double)numbers/(double)xes;
            cout << res << "\n";
        }
    }
    return 0;
}