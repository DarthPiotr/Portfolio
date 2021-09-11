#include <iostream>
#include <vector>

using namespace std;

int g, w, b, total, m;
struct piece{
    piece(char c, short x, short y) : code(c), x(x), y(y) {}
    char code;
    short x, y;
};
struct gameboard : vector<piece>{
public:
    char state[4][4] = {0};
    void add(char c, char x, short y){
        this->push_back(piece(c, x-'A', y-1));
        state[x-'A'][y-1] = size();
    }

    inline piece pieceat(short x, short y){
        return this->at(state[x][y]-1);
    }

    inline bool iswhiteat(short x, short y){
        return state[x][y]-1 < w;
    }

    void print(){     
        for(short i = 3; i >= 0; --i){
            cerr << i+1 << "  ";
            for(short j = 0; j < 4; ++j){
                if(state[j][i] == 0) cerr << "-- ";
                else cerr << (iswhiteat(j,i) ? "w" : "b") << pieceat(j,i).code << " ";
            }
            cerr << "\n";
        }
        cerr << "   ";
        for(short i = 0; i < 4; ++i) cerr << " " << (char)(i+'A') << " ";
        cerr << "\n";
    }
}board;


int main (){
    ios_base::sync_with_stdio(0);
    int i, j;
    char a, b;
    cin >> g;
    while(g--){
        board.clear();
        cin >> w >> b >> m;
        total = w+b;
        for(i = 0; i < total; ++i){
            cin >> a >> b >> j;
            board.add(a, b, j);
        }
    }

    board.print();

    return 0;
}