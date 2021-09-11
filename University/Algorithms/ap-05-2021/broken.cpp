#include <iostream>
#include <string>
#include <map>

using namespace std;

int keys_allowed;
string line;

int main (){
    //ios_base::sync_with_stdio(0);
    
    int i, len;
    int beg, char_c, max;
    do {
        cin >> keys_allowed;
        if(keys_allowed == 0) break;
        cin.ignore();
        getline(cin, line);
        len = line.size();

        //cerr << len << " \""<<line<<"\"\n";

        map<char, int> m;
        beg = 0;
        char_c = 0;
        max = 0;
        for(i = 0; i < len; ++i){
            
            if(m[line[i]] == 0) ++char_c;
            ++m[line[i]];
            while(char_c > keys_allowed){
                --m[line[beg]];
                if(m[line[beg]] == 0) --char_c;
                ++beg;
            }


            if(i - beg + 1 > max) max = i - beg + 1;
        }
        cout << max << "\n";

    }while(keys_allowed != 0);
    return 0;
}