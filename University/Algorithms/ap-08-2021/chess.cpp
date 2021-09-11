#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<short, short> pss;
typedef vector<pss> vpss;

int g, w, b, total, m;
struct piece{
    char type, code;
    bool color; // 1 = white 0 = black
    piece() : type('0'), code('0'){}
    piece(char t, char c) : type(t), color(c)
    {
        code = (color ? 'A' : 'a') + (type - 'A');
    }    
};

struct board{
    piece b[4][4];

    void add(piece p, short x, short y){
        b[x][y] = p;
    }
    void display(){
        for(short i = 3; i >= 0; --i){
        cerr << i+1 << " ";
            for(short j = 0; j < 4; ++j)
                cerr << b[j][i].code << " ";
            cerr << "\n";
        }
        cerr << "* ";
        for(short i = 0; i < 4; ++i) cerr << (char)(i+'A') << " ";
        cerr << "\n";
    }
    string getcode(){
        string s = "";
        for(short i = 3; i >= 0; --i)
            for(short j = 0; j < 4; ++j)
                s += b[j][i].code;
        return s;
    }
};

inline bool onboard(const short &x, const short &y){
    return x < 4 && x >= 0 && y < 4 && y >= 0;
}

vpss prepareknight(short x, short y){
    vpss res;
    short knight_x[] = {-1, 1, 2,  2,  1, -1, -2, -2}; // 8
    short knight_y[] = { 2, 2, 1, -1, -2, -2, -1,  1};
    short xt, yt;

    for(short i = 0; i < 8; ++i){
        xt = x+knight_x[i], yt = y+knight_y[i];
        if(onboard(xt, yt))
            res.push_back(pss(xt, yt));
    }
    return res;
}

vpss preparestraight(board &board, short x, short y){
    vpss res;

    short k, xt, yt;
    for(k = 1; k <= 3; ++k){ // up
        xt = x+k, yt=y;
        if(!onboard(xt, yt)) break;
        res.push_back(pss(xt, yt));
        if(board.b[xt][yt].code != '0') break;
    }
    for(k = 1; k <= 3; ++k){ // down
        xt = x-k, yt=y;
        if(!onboard(xt, yt)) break;
        res.push_back(pss(xt, yt));
        if(board.b[xt][yt].code != '0') break;
    }
    for(k = 1; k <= 3; ++k){ // right
        xt = x, yt=y+k;
        if(!onboard(xt, yt)) break;
        res.push_back(pss(xt, yt));
        if(board.b[xt][yt].code != '0') break;
    }
    for(k = 1; k <= 3; ++k){ // left
        xt = x, yt=y-k;
        if(!onboard(xt, yt)) break;
        res.push_back(pss(xt, yt));
        if(board.b[xt][yt].code != '0') break;
    }   

    return res;
}

vpss preparediagonal(board &board, short x, short y){
    vpss res;

    short k, xt, yt;
    for(k = 1; k <= 3; ++k){
        xt = x+k, yt=y+k;
        if(!onboard(xt, yt)) break;
        res.push_back(pss(xt, yt));
        if(board.b[xt][yt].code != '0') break;
    }
    for(k = 1; k <= 3; ++k){
        xt = x+k, yt=y-k;
        if(!onboard(xt, yt)) break;
        res.push_back(pss(xt, yt));
        if(board.b[xt][yt].code != '0') break;
    }
    for(k = 1; k <= 3; ++k){
        xt = x-k, yt=y+k;
        if(!onboard(xt, yt)) break;
        res.push_back(pss(xt, yt));
        if(board.b[xt][yt].code != '0') break;
    }
    for(k = 1; k <= 3; ++k){
        xt = x-k, yt=y-k;
        if(!onboard(xt, yt)) break;
        res.push_back(pss(xt, yt));
        if(board.b[xt][yt].code != '0') break;
    }   

    return res;
}

vpss preparemoves(board &board, short x, short y){
    vpss res;

    switch(board.b[x][y].type){
        case 'N':
            res = prepareknight(x, y);
            break;
        case 'R':
            res = preparestraight(board, x, y);
            break;
        case 'B':
            res = preparediagonal(board, x, y);
            break;
        case 'Q':
            res = preparestraight(board, x, y);
            vpss vec = preparediagonal(board, x, y);
            res.insert(res.end(), vec.begin(), vec.end());
            break;
    }

    return res;
}

//map<string, bool> visited;

bool solve(board br, short move){ // return if white won
    //cerr << "> " << move << "\n";
    //br.display();
    if(move > m) { // black wins if too many moves
        //for(short u = 0; u < move; ++u) cerr << "-";
        //cerr << "0 won (moves limit exceeded)\n";
        return false;
    }
    
    short i, j;
    vpss possiblemoves;
    piece *from, *to;
    bool currcolor = move%2;
    
    // lets consider all possible moves, for [currcolor] piece.
    for(i = 3; i >= 0; --i){
        for(j = 0; j < 4; ++j){
            from = &br.b[j][i];
            if(from->code != '0' && from->color == currcolor){ // not empty and right color
                possiblemoves = preparemoves(br, j, i);
                //cerr << "possible moves: " << possiblemoves.size() << "\n";
                for(auto mv = possiblemoves.begin(); mv != possiblemoves.end(); ++mv){ // for each move
                    to = &(br.b[mv->first][mv->second]);
                    if(to->code != '0' && from->color == to->color) continue; // dont capture same color
                    if(to->type == 'Q'){ // currcolor wins when it caputres the queen
                        //for(short u = 0; u < move; ++u) cerr << "-";
                        //cerr << currcolor << " won in move "<<move<<" by capturing the queen\n";
                        return currcolor;
                    }
                    //if(to->type == '0' || to->color == !currcolor){ 
                        
                        // any other valid move
                        board newboard = br;    // prepare new board
                        newboard.b[j][i] = piece();
                        newboard.b[mv->first][mv->second] = *from;
                        //cerr << "Trying to move:\n";
                        //newboard.display();
                        //cerr << "^^^^^^^^^^^^^^^^\n";
                        if(currcolor == solve(newboard, move+1)){ // if this color wins later, we're certain that it wins also now
                            //for(short u = 0; u < move; ++u) cerr << "-";
                            //cerr << "passing down victory of " << currcolor << "\n";
                            return currcolor;
                        }
                    //}
                }
            }
        }
    }
    //for(short u = 0; u < move; ++u) cerr << "-";
    //cerr << !currcolor << " won in move "<<move<<" cause no other moves made "<<currcolor<<" win\n";
    return !currcolor; // the second one won if none of the moves lead to [currcolor] winning
}

int main (){
    ios_base::sync_with_stdio(0);
    int i, j;
    char c1, c2;
    cin >> g;
    while(g--){
        board bboard;
        //visited.clear();
        cin >> w >> b >> m;
        total = w+b;
        for(i = 0; i < total; ++i){
            cin >> c1 >> c2 >> j;
            bboard.add(piece(c1, i < w), c2-'A', j-1);
        }
        //bboard.display();
        //visited[bboard.getcode()] = true;
        cout << (solve(bboard, 1) ? "YES\n" : "NO\n");
    }
    

    return 0;
}