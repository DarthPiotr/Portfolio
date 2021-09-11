#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

map<string, vector<string>> graph;
map<string, bool> visited;

// DFS
void trasa(string pocz, string koniec, int d){
    if(pocz == koniec){
        for(int i = 0; i < d; ++i) cout << "  ";
        cout << "END!\n";
        return;
    }

    for(auto &child : graph[pocz] ){
        //if(visited[child] == 0){
            for(int i = 0; i < d; ++i) cout << "  ";
            cout << child << "\n";
            //visited[child] = 1;
            trasa(child, koniec, d+1);
        //}
    }
}

void trasa2(int pocz, int koniec){
    if(pocz == koniec-1) return;

    int nowy_koniec = koniec-1;
    trasa2(pocz, nowy_koniec);
}

int main(){

    graph["a"].push_back("b");
    graph["a"].push_back("c");
    graph["b"].push_back("c");
    graph["b"].push_back("d");
    graph["c"].push_back("e");
    graph["c"].push_back("f");
    graph["d"].push_back("f");
    graph["e"].push_back("f");

    string beg = "a";
    cout << beg << "\n";
    trasa(beg, "e", 1);

    return 0;
}