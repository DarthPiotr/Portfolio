#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int n;
long long res[50001];

int main (){
    ios_base::sync_with_stdio(0);

    int i, curr_len;
    vector<int> tasks;
    map<int, vector<int>> lengths; // k: lenght, v: task numbers
    cin >> n;

    for(i = 0; i < n; ++i){
        cin >> curr_len;
        if(curr_len == 1) res[i] = i+1;
        else {
            tasks.push_back(i);
            lengths[curr_len].push_back(i);
        }
    }

    

    int key, cycle=2;
    
    long long tick = n; // since we start at second cycle, we already passed through n tasks]
    //cerr << "Starting at tick " << tick << "\n";
    while(!lengths.empty()){
        long long size = tasks.size();
        //cerr << "Tasks size: " << size << ", lenghts size: " << lengths.size() << "\n";

        auto len = lengths.begin();
        key = len->first; // get first length
        //cerr << "Considering all with length of " << key << "\n";

        // key - cycle          : how many cycles have passed since last full cycle
        // (key-cycle) * size   : how many time ticks it was
        // (key-cycle)*size + 1 : we want to be at the first tick of next cycle
        tick += (key - cycle)*size + 1;
        //cerr << "Starting at cycle " << cycle+1 << " with tick " << tick << "\n";

        for(auto v : len->second){

            //cerr << "Found that element #" << v << " is at position " << lower_bound(tasks.begin(), tasks.end(), v) - tasks.begin() << "\n";
            //cerr << "Its finishing time will be set to " << tick + lower_bound(tasks.begin(), tasks.end(), v) - tasks.begin() << "\n";
            // result is time of the current cycle + task offset (i.e. position at vector)
            res[v] = tick + lower_bound(tasks.begin(), tasks.end(), v) - tasks.begin();
        }

        /*cerr << "Tasks:\n";
        for(auto &t : tasks)
            cerr << t << " ";
        cerr << "\n";*/
        
        for(auto v : len->second){
            // remove used tasks from list after(!!!) all the end ticks were computed
            //cerr << "Erasing element " << v << "\n";
            tasks.erase(lower_bound(tasks.begin(), tasks.end(), v));
        }

        /*cerr << "Tasks:\n";
        for(auto &t : tasks)
            cerr << t << " ";
        cerr << "\n";*/

        tick += size - 1;   // set current tick to the end of current cycle
                            // (which is [size] long, but we're already at first tick, thus we must substract one)
        lengths.erase(len); // we won't need current one 

        cycle = key+1; // next cycle number is one higher than current one.
    }

    for(i = 0; i < n; ++i)
        cout << res[i] << "\n";


    return 0;
}