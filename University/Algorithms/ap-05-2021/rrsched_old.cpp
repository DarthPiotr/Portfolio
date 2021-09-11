#include <iostream>
#include <map>

using namespace std;

struct info{
    long long  prefixsum = 0, // prefix sum of lengths including current length
    prev_prefixsum = 0;       // prefix sum of lenghts excluding current length
    int quantity = 0,         // quantity of current length
    quantity_sum = 0;         // quantity of <= lengths
};

int n;
int eq_before[50001] = {0};
map<int, info> prefixsum_map;

int main (){

    int i, curr_len, ps, qs;
    ios_base::sync_with_stdio(0);
    cin >> n;

    for(i = 0; i < n; ++i){
        cin >> curr_len;

        eq_before[i] = prefixsum_map[curr_len].quantity;
        ++prefixsum_map[curr_len].quantity;
    }

    ps = 0; qs = 0;
    for(auto &kv : prefixsum_map){ // keys are sorted idk why tho
        qs += kv.second.quantity;
        kv.second.quantity_sum = qs;

        kv.second.prev_prefixsum = ps;
        ps += kv.first * kv.second.quantity;
        kv.second.prefixsum = ps;

        cerr << kv.first << " => q: " << kv.second.quantity << " ps: " << kv.second.prefixsum << "\n";
    }



    return 0;
}