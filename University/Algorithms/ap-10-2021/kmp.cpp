#include <iostream>

#define SIZE 1'000'000

using namespace std;

void find(string pat, string txt){

    int plen = pat.size(),
        tlen = txt.size();

    int lps[SIZE];
    
    // preprocessing
    int len = 0; lps[0] = 0;
    for(int i = 1; i < plen; ){
        if(pat[len] == pat[i])  // match
            lps[i++] = ++len;   // save current length, move index
        else {  // not match
            if(len == 0) lps[i++] = 0;  // no matches before - set 0 and move forward
            else len = lps[len-1];      // mismatch after match - reset len with previous lps position
        }
    }

    // searching
    int pi = 0, ti = 0;
    while(ti < tlen){
        if(pat[pi] == txt[ti])  // match, increment both
            ++pi, ++ti;

        if(pi == plen) {             // end of the pattern = found it
            cout << ti - pi << "\n"; // difference = beginning of pattern
            pi = lps[pi-1];          // reset pattern index
        }
        else if(ti < tlen && pat[pi] != txt[ti]){ // mismatch and not end of text
            if(pi != 0) pi = lps[pi-1];     // if pattern was matched, reset it using lps
            else ++ti;                      // pattern not matched - go on with text index
        }
    }
}

int main (){
    ios_base::sync_with_stdio(0);
    int test, n;
    string pattern, text;
    cin >> test;
    while(test--){
        cin >> n >> pattern >> text;
        find(pattern, text);
    }

    return 0;
}