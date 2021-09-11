#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
 
#define MAX_STALLS 100000
#define SHORT_STALLS 1000
int big_stall_size = MAX_STALLS/SHORT_STALLS;
 
bool barn_stalls[MAX_STALLS];
int barn_rooms[SHORT_STALLS];
bool barn_switched[SHORT_STALLS];
 
int N, R;
bool q;
int a, b;
 
int sum_every(int from, int to){
    int suma = 0;
    for(int i=from; i<=to; i++){
        if(barn_stalls[i]) suma++;
    }
    if(barn_switched[from/big_stall_size]) return to - from + 1 - suma;
    return suma;
}
 
int sum_ligths(int start, int end){
    int suma = 0;
    int short_start = start/big_stall_size;
    int short_end = end/big_stall_size;
    if(short_start == short_end){
        return sum_every(start, end);
    }
    else{
        suma = sum_every(start, (short_start+1)*big_stall_size-1) + sum_every(short_end*big_stall_size, end);
        for(int i=short_start+1; i<short_end; ++i){
            if(barn_switched[i]){
                suma += (big_stall_size - barn_rooms[i]);
            }
            else{
                suma += barn_rooms[i];
            }
        }
        return suma;
    }
}
 
void light_switch(int start, int end){
    int short_start = start/big_stall_size; //0 - 0
    int short_end = end/big_stall_size; // 549 - 5
    if(short_start == short_end){
        for(int i=start; i<=end; ++i){
            if(barn_stalls[i]) barn_rooms[short_start]--;
            else barn_rooms[short_start]++;
            barn_stalls[i] = !barn_stalls[i];
        }
        return;
    }
    for(int i=start; i<=(short_start + 1) * big_stall_size-1; ++i){
        if(barn_stalls[i]) barn_rooms[short_start]--;
        else barn_rooms[short_start]++;
        barn_stalls[i] = !barn_stalls[i];
    }
    for(int i=short_end*big_stall_size; i<=end; ++i){
        if(barn_stalls[i]) barn_rooms[short_end]--;
        else barn_rooms[short_end]++;
        barn_stalls[i] = !barn_stalls[i];
    }
    for(int i=short_start+1; i<short_end; ++i){
        barn_switched[i] = !barn_switched[i];
    }
    return;
}
 
int main() {
    cin>>N>>R;
    for(int i=0; i<R; ++i){
        cin>>q>>a>>b;
        if(q){
            cout<<sum_ligths(a-1, b-1)<<endl;
        }
        else{
            light_switch(a-1,b-1);
        }

        cerr << "Tree:\n ";
        int cnt = 2;
        int begspace = base;
        for(int j = 0; j < base - cnt; ++j) cerr << " ";
        for(int i = 1; i <= 2*base; ++i){
            cerr << tree[i];
            for(int j = 0; j < (begspace<<1)-1; ++j) cerr << " ";
            if(i == cnt-1){
                cerr << "\n";
                for(int j = 0; j < (begspace>>1)-1; ++j) cerr << " ";
                cnt = cnt << 1;
                begspace = begspace >> 1;
            }
        }
        cerr << "\n\n";

    }
    return 0;
}