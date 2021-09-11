#include <iostream>
#include <string>

#define Z (short)'0'

using namespace std;


// na potrzeby zadania czas jest przestawiany jako int: 60*[hh] + [mm]

// pre-generowana lista czasow kiedy sie pokrywaja
/*
for(int i = 0; i < 22; i ++){
    tab [i] = 60*i + ceil(i*60.0/11);
}
*/
short tab[22] = {0, 66, 131, 197, 262, 328, 393, 459, 524, 590, 655, 720, 786, 851, 917, 982, 1048, 1113, 1179, 1244, 1310, 1375};

int binSearch(int beg, int end, int value){
    if(beg == end)
        return beg;
    
    int mid = (beg+end)/2;

    if(tab[mid+1] > value)
        return binSearch(beg, mid, value);
    return binSearch(mid+1, end, value);
}

int main(){

    ios_base::sync_with_stdio(false);

    int n;
    short start, end;
    string time;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> time;
        start = 600*(time[0] - Z) + 60*(time[1] - Z) + 10*(time[3]-Z) + time[4]-Z;
        cin >> time;
        end = 600*(time[0] - Z) + 60*(time[1] - Z ) + 10*(time[3]-Z) + time[4]-Z;

        cout << binSearch(0, 21, end) - binSearch(0, 21, start) << "\n";   
    }

    return 0;
}