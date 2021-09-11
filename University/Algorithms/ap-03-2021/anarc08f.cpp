#include <iostream>
#include <map>
#include <vector>
#include <cstring>

#define __DEBUG__
#define MIN_TO 2000000

using namespace std;

struct city;

struct road{
    int len;
    city* to;
};

struct city{
    int index;
    int min_to;
    int min_from;
    vector<road> conn;
} cities[101]; // [1:N]; broken[1]=garage
int broken[1001]; // [0:C] ; broken[0]=garage

int N, C, R;
map<string, int> city_numbers;
int c_n;

void full_dijkstra(){
    bool visited[101] = {0};
    int min_i, min_l;
    int i, j;

    min_i = broken[0];

    cities[min_i].min_to = 0;

    for(j = 0; j < N; ++j){
        min_l = MIN_TO;
        for(i = 1; i <= N; ++i){
            if(!visited[i]){
                if(cities[i].min_to < min_l){
                    min_i = i;
                    min_l = cities[i].min_to;
                }
            }
        }
        visited[min_i] = true;

        for(const auto & r : cities[min_i].conn){
            r.to->min_to = min(r.to->min_to, cities[min_i].min_to + r.len);
        }
    }
}

int shortest_path(int from){
    if(cities[from].min_from != MIN_TO)
        return cities[from].min_from;

    bool visited[101] = {0};
    int length[101];
    memset(length, 0x11111111, sizeof(length));
    int min_i, min_l;
    int i, j;

    min_i = from;

    length[min_i] = 0;

    for(j = 0; j < N; ++j){
        min_l = MIN_TO;
        for(i = 1; i <= N; ++i){
            if(!visited[i]){
                if(length[i] < min_l){
                    min_i = i;
                    min_l = length[i];
                }
            }
        }
        visited[min_i] = true;

        for(const auto & r : cities[min_i].conn){
            length[r.to->index] = min(length[r.to->index], length[min_i] + r.len);
        }
    }


#ifdef __DEBUG__
        cerr << "From " << from << " to:\n";
        for(j = 1; j <= N; ++j){
            cerr << "-> " << j << ": " << length[j] << "\n";
        }
#endif

    cities[from].min_from = length[1];
    return cities[from].min_from;
}

int main (){

    ios_base::sync_with_stdio(0);

    int i, j, a, b, len, cnt;
    string tmp;
    char c;
    bool to_a, to_b;
    road r;

    cnt = 1;
    do{
        cin >> N >> C >> R;
        if(N == 0) break;

        memset(cities, 0, sizeof(cities));
        memset(broken, 0, sizeof(broken));
        city_numbers.clear();
        c_n = 1;

#ifdef __DEBUG__
        cerr << "\t==== NEW CASE ====\n";
        //cerr << "N: "<<N<<", C: "<<C<<", R: "<<R<<"\n";
#endif

        for(i = 0; i <= C; ++i){
            cin >> tmp;
             if(city_numbers[tmp] == 0){ // new city
                city_numbers[tmp] = c_n;
                cities[c_n].index = c_n;        
                cities[c_n].min_to = MIN_TO;
                cities[c_n].min_from = MIN_TO;
                ++c_n;
            }
            broken[i] = city_numbers[tmp];
        }     

        for(i = 0; i < R; ++i){

            cin >> tmp; // city a
            if(city_numbers[tmp] == 0){ // new city
                city_numbers[tmp] = c_n;
                cities[c_n].index = c_n;
                cities[c_n].min_to = MIN_TO;
                cities[c_n].min_from = MIN_TO;
                ++c_n;
            }
            a = city_numbers[tmp];

            // road description
            cin >> c;
            to_a = c == '<';

            len = 0;
            cin >> c >> c;
            while (c != '-'){
                len *=10;
                len += c - '0';
                cin >> c;
            }    
            cin >> c;
            to_b = c == '>';       

            cin >> tmp; // city b
            if(city_numbers[tmp] == 0){ // new city
                city_numbers[tmp] = c_n;
                cities[c_n].index = c_n;
                cities[c_n].min_to = MIN_TO;
                cities[c_n].min_from = MIN_TO;
                ++c_n;
            }
            b = city_numbers[tmp];

            r.len = len;
            if(to_a){
                r.to = &cities[a];
                cities[b].conn.push_back(r);
            }
            if(to_b){
                r.to = &cities[b];
                cities[a].conn.push_back(r);
            }
        }

        full_dijkstra();

        len = 0;
        for(i = 1; i <= C; ++i)
            len += cities[broken[i]].min_to + shortest_path(broken[i]);

        cout << cnt << ". " << len << "\n";
        ++cnt;
        
#ifdef __DEBUG__
        // debug display
        for(const auto& kv : city_numbers){
            cerr << kv.second << " (" << kv.first << "): ";
            for(const auto& e : cities[kv.second].conn){
                cerr << e.to->index << " (" << e.len << "), ";
            }
            cerr << " => " << cities[kv.second].min_to << "\n";
        }

        cerr << "Broken:\n";
        for(i = 0; i <= C; ++i)
            cerr << broken[i] << " ";
        cerr << "\n";
#endif
    }while(N != 0);

    return 0;
}