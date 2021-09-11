#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>

#define SIZE 100001

using namespace std;

int n, p;
vector<int> graph[SIZE];
bool visited[SIZE] = {0};

int DFS(int begin){
    //cerr << begin << " ";
    int num = 1;
    for(auto &child : graph[begin]){
        if(!visited[child]){
            visited[child] = true;
            num += DFS(child);
        }
    }
    return num;
}

int main(){
    ios_base::sync_with_stdio(0);
    int a, b, i, j;
    cin >> n >> p;
    while(p--){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    long long ans = 0;
    int sum = 0;
    int res;
    for(i = 0; i < n; ++i){
        if(!visited[i]){
            visited[i] = true;
            res = DFS(i);
            ans += sum*res;
            sum += res;
        }
    }

    /*for(auto &kv : groups){
        cerr << kv.first << " " << kv.second << "\n";
    }*/

    /*for(auto it = groups.begin(); it != groups.end(); ++it){
        //it->second--;
        ans += it->first * it->first * ((it->second-1)*it->second)/2;
        auto it2 = it;
        for(it2++; it2 != groups.end(); ++it2){
            cerr << it->first<<" * "<<it->second<<" * "<<it2->first<<"\n";
            ans += it->first * it->second * it2->first * it2->second;
        }
    }*/

    cout << ans << "\n";

    return 0;
}