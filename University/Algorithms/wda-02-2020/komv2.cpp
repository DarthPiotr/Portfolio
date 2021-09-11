#include <iostream>
#include <string>

using namespace std;

char c;
string buffer, buffer2;
bool insideOneLineComment = false;
bool insideMultilineComment = false;
bool insideSingleQuote = false;
bool insideDoubleQuote = false;
bool ignoreChar = false;

bool isComment() {
    return insideOneLineComment || insideMultilineComment;
}

int main() {

    while (cin.get(c)) {
        //cout << (int)c << " -> \"" << c << "\"\n";

        switch (c) {
        case '/':
            buffer = c;
            cin.get(c);
            buffer += c;

            if (insideDoubleQuote) {
                cout << buffer;
                buffer = "";
            }
            else if (!isComment()) {
                if (buffer == "//") {
                    insideOneLineComment = true;
                }
                else if (buffer == "/*") {
                    insideMultilineComment = true;
                }
                else
                {
                    //cout << "!BUFFER /!\n";
                    cout << buffer;
                    buffer = "";
                }
            }
            break;
        case '*':
            buffer = c;
            cin.get(c);

            /*while(c == '\\'){
                buffer2 = c;
                cin.get(c);
                buffer2 += c;

                if(c == '\n'){
                    cout << "\n";
                }
                else{
                    cout << buffer2;
                }
            }*/

            buffer += c;

            if (buffer == "*/" && insideMultilineComment) {
                insideMultilineComment = false;
            }
            else
            {
                cout << buffer;
                buffer = "";
            }
            break;
        case '\"':
            if (!isComment()) {
                insideDoubleQuote ^= 1;
                cout << c;
            }
            break;
        case '\n':
            insideOneLineComment = false;

            if (!isComment()) {
                //cout << "!com!\n";
                cout << c;
            }
            break;
        case '\\':
            buffer = c;
            cin.get(c);
            buffer += c;

            if (insideOneLineComment && c == '\n') {
                insideOneLineComment = true;
            }
            else if (c == '\"') {
                cout << "\\\"";
                buffer = "";
            }
            else
            {
                cout << buffer;
                buffer = "";
            }
            break;
        default:

            if (!isComment()) {
                //cout << "!com!\n";
                cout << c;
            }

            break;
        }
    }

    return 0;
}