#include <iostream>
#include <string>

using namespace std;

// WLK  |     ||     |
// LIT. | '_' || C++ | Java
//------------------------------
//  0   |  0  ||  1  |  1
//  0   |  1  ||  1  |  0
//  1   |  0  ||  0  |  1
//  1   |  1  ||  0  |  0

string line, tmp;
bool upp, und;

int main(){
    char c;
    ios_base::sync_with_stdio(0);

    while(getline(cin, line)){
        upp = und = true;

        if(islower(line[0])){
            upp = und = false;

            for(int i = 0; i < (int)line.size(); i++){
                c = line[i];

                // jesli _
                if(c == '_'){
                    und = true;
                    // jesli obecny znak nie jest ostatni ani pierwszy
                    if(i+1 < (int)line.size() && i != 0){
                        // a nastepny jest mala litera
                        if(islower(line[i+1])){
                            // to zamien _ i mala litere na duza
                            line.replace(i,2,1,(char)toupper(line[i+1]));
                        }
                        // jesli nastepny to _, to BLAD!
                        /*else if(line[i+1] == '_'){
                            line.erase(i--, 1);
                        }*/
                        // jesli nastepny jest duzy to blad
                        else{
                            upp = true;
                            break;
                        }
                    }
                    // jesli pierwszy lub ostatni to BLAD!  //po prostu usun
                    else{
                        //line.erase(i--, 1);
                        upp = true;
                        break;
                    }
                }

                // jesli duza litera
                if(isupper(c)){
                    upp = true;
                    tmp = "_";
                    tmp += (char)tolower(c);
                    line.replace(i, 1, tmp);
                }

                // jesli wystapila i duza i podloga, to error
                if(und && upp){
                    break;
                }
            }
        }

        cout << (und && upp ? "Error!" : line) << "\n";
    }

    return 0;
}