#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

string tab[101];
short s, t, n;

int Hash(string key) {
    int sum = 0, len = key.size();
    for (int i = 0; i < len; i++) {
        sum += (int)key[i] * (i + 1);
    }
    return (19 * sum) % 101;
}

void insert(string key) {
    int hash = Hash(key);
    int index, indexok = -1;
    for (int i = 0; i < 20; i++) {
        index = (hash + i * i + 23 * i)%101;
        if (tab[index] == key)
            return;
        if (indexok < 0 && tab[index] == "") {
            indexok = index;
        }
    }
    if(indexok >= 0) {
        tab[indexok] = key;
        s++;
    }
}

void remove(string key) {
    int hash = Hash(key);
    int index;
    for (int i = 0; i < 20; i++) {
        index = (hash + i * i + 23 * i) % 101;
        if (tab[index] == key) {
            tab[index] = "";
            s--;
            return;
        }
    }
}

int rrand(int min, int max){
    return min + rand()%(max-min+1);
}

string alp = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuioplkjhgfdsazxcvbnm";
string sgen(){
    int l = rrand(1, 15);
    string s = "";
    for(int i = 0; i < l; i++)
        s += alp[rrand(0, alp.size()-1)];
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    srand(time(NULL));
    short i, j;
    string tmp;
    
    ofstream sample;
    ofstream result;
    sample.open("hash_input.txt");
    result.open("hash_result.txt");

    t = 5;
    sample << t << "\n";

    for (i = 0; i < t; i++) {
        n = rrand(100, 1000);
        sample << n << "\n";

        s = 0;
        for (j = 0; j < 101; j++) {
            tab[j] = "";
        }

        for (j = 0; j < n; j++) {
            tmp = sgen();


            bool aha = rrand(0, 1);
            if (aha || s < 1){
                sample << "ADD:" << tmp << "\n";
                insert(tmp);
            }
            else if (!aha || s > 999 ){
                sample << "DEL:" << tmp << "\n";
                remove(tmp);
            }
        }

        result << s << "\n";
        for (j = 0; j < 101; j++) {
            if (tab[j] != "")
                result << j << ":" << tab[j] << "\n";
        } 
    }

    sample.close();
    result.close();

    return 0;
}