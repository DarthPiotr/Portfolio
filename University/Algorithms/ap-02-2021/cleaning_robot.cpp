#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>

#define MAXBEST 10000

using namespace std;

struct vert;

struct edge{
    vert* to;
    short len;
};

struct vert{
    short i, j;
    short index;
    char type;
    vector<edge> edges;
} map[21][21];
vert* graph[11]; // graph[0] - robot start
short vertnum;

int w, h;

void distance(){
    short distance[21][21]; // -1 = cannot reach
    bool visited[21][21];

    queue<vert*> q_vert;
    queue<short> q_dist;
    vert* curr_vert;
    short curr_dist;

    for(short i = 0; i < vertnum; ++i){
        //cerr << "Starting for i=" << i << "\n";

        // make sure everyhing is cleared
        memset(distance, -1, sizeof(distance));
        memset(visited, false, sizeof(visited));
        q_dist = queue<short>();
        q_vert = queue<vert*>();
        curr_dist = 0;


        // add inital tile
        curr_vert = graph[i];
        visited[curr_vert->i][curr_vert->j] = true;
        q_vert.push(curr_vert);
        q_dist.push(curr_dist);

        while(!q_vert.empty()){

            // get tile and distance from queue
            curr_vert = q_vert.front();
            q_vert.pop();
            curr_dist = q_dist.front();
            q_dist.pop();

            //cerr << "Element at: (" << curr_vert->i << ", " << curr_vert->j << ") " << (curr_vert->type == '*' || curr_vert->type == 'o' ? curr_vert->type : ' ') << "\n";

            // set distance to tile
            distance[curr_vert->i][curr_vert->j] = curr_dist;
            
            // add edge to graph if dirty
            if( (curr_vert->i != graph[i]->i ||  curr_vert->j != graph[i]->j) // different position
                && curr_vert->type == '*'  // dirty tile (no need for edges back to start)
                ) {
                //cerr << "Adding edge: (" << graph[i]->i << ", " << graph[i]->j << ") -> (" << curr_vert->i << ", " << curr_vert->j << ") len: " << curr_dist << "\n";
                edge e;
                e.len = curr_dist;
                e.to = curr_vert;
                graph[i]->edges.push_back(e);
            }
            
            // add neighbours to queue
            if(curr_vert->i - 1 >= 1){  // ^ 
                if(!visited[curr_vert->i - 1][curr_vert->j]){
                    visited[curr_vert->i - 1][curr_vert->j] = true;
                    if(map[curr_vert->i - 1][curr_vert->j].type != 'x'){ // not wall
                        //cerr << "  push ==> (" << curr_vert->i - 1 << ", " << curr_vert->j << ")\n";
                        q_vert.push(&map[curr_vert->i - 1][curr_vert->j]);
                        q_dist.push(curr_dist + 1);
                    }
                }
            }
            if(curr_vert->i + 1 <= h){  // v 
                if(!visited[curr_vert->i + 1][curr_vert->j]){
                    visited[curr_vert->i + 1][curr_vert->j] = true;
                    if(map[curr_vert->i + 1][curr_vert->j].type != 'x'){ // not wall
                        //cerr << "  push ==> (" << curr_vert->i + 1 << ", " << curr_vert->j << ")\n";
                        q_vert.push(&map[curr_vert->i + 1][curr_vert->j]);
                        q_dist.push(curr_dist + 1);
                    }
                }
            }
            if(curr_vert->j - 1 >= 1){  // < 
                if(!visited[curr_vert->i][curr_vert->j - 1]){
                    visited[curr_vert->i][curr_vert->j - 1] = true;
                    if(map[curr_vert->i][curr_vert->j - 1].type != 'x'){ // not wall
                        //cerr << "  push ==> (" << curr_vert->i << ", " << curr_vert->j-1 << ")\n";
                        q_vert.push(&map[curr_vert->i][curr_vert->j - 1]);
                        q_dist.push(curr_dist + 1);
                    }
                }
            }
            if(curr_vert->j + 1 <= w){  // >
                if(!visited[curr_vert->i][curr_vert->j + 1]){
                    visited[curr_vert->i][curr_vert->j + 1] = true;
                    if(map[curr_vert->i][curr_vert->j + 1].type != 'x'){ // not walls
                        //cerr << "  push ==> (" << curr_vert->i << ", " << curr_vert->j+1 << ")\n";
                        q_vert.push(&map[curr_vert->i][curr_vert->j + 1]);
                        q_dist.push(curr_dist + 1);
                    }
                }
            }

            
        }

        if(i == 0){ // if start position
            if((int)graph[0]->edges.size() < vertnum-1){ // cannot reach all dirt tiles
                return;
            }
        }
/*
        ////////
        cerr << "Point " << i << ": \n";
        for(int a = 1; a <= h; ++a){
            for(int b = 1; b <= w; ++b){
                cerr << setw(3) << distance[a][b];
            }
            cerr << "\n";
        }
        cerr << "\n";
        ///////
 */       
    }
}

short DFS_bnb(short index, short distance, short depth, short best_dist = MAXBEST, short visited = 0){
    //for(short i = 0; i < depth; ++i) cerr << " ";
    //cerr << "(d: "<<depth<<") Visiting: " << index << ", dst: " << distance << "\n";
    
    visited |= 1 << index; // set index to visited
    short curr_dist;
    for(short i = 0; i < (short)graph[index]->edges.size(); ++i){  // check every edge
        if( (visited & (1 << graph[index]->edges[i].to->index)) == 0    // if not visited
            && distance + graph[index]->edges[i].len < best_dist        // and new distance isnt worse than best so far
        ){
            curr_dist = DFS_bnb(graph[index]->edges[i].to->index,       // get new distance
                                distance + graph[index]->edges[i].len,
                                depth+1,
                                best_dist,
                                visited);
            //for(short i = 0; i < depth; ++i) cerr << " ";
            //cerr << "(d: "<<depth<<") DFS returnes dist: " << curr_dist << "\n";
            if(curr_dist < best_dist){
                best_dist = curr_dist;
            }
        }
    }
    //for(short i = 0; i < depth; ++i) cerr << " ";
    //cerr << "Best dist: " << best_dist << "\n";

    if (depth == vertnum-1){
        //cerr << "END.\n";
        return distance < best_dist ? distance : MAXBEST;
    }

    return best_dist == MAXBEST ? distance : best_dist;
}

int main (){
    //ios_base::sync_with_stdio(0);
    short i, j;

    do {
        cin >> w >> h;
        if(w == 0 && h == 0) break;
        if(w == 0 || h == 0){
            cout << "-1\n";
            continue;
        }
        //cerr << "\t\t==== NEW CASE ====\n";

        vertnum = 1;
        for(i = 1; i <= h; ++i){
            for(j = 1; j <= w; ++j){
                cin >> map[i][j].type;
                //cerr << map[i][j].type;
                map[i][j].i = i;
                map[i][j].j = j;
                map[i][j].edges.clear();
                switch(map[i][j].type){  
                    case 'o':
                        graph[0] = &map[i][j];
                        graph[0]->index = 0;
                        break;
                    case '*':
                        graph[vertnum] = &map[i][j];
                        graph[vertnum]->index = vertnum;
                        ++vertnum;
                        break;                   
                }  
            }
            //cerr << "\n";
        }

        distance();

        /*cerr << "Graph :\n";
        for(int i = 0; i < vertnum; ++i){
            cerr << "vertex ("<< graph[i]->i <<", "<<graph[i]->j<<") id: " << graph[i]->index << "\n";
            for(int k = 0; k < graph[i]->edges.size(); ++k)
            cerr << "edge: " << graph[i]->index << " -> " << graph[i]->edges[k].to->index << " len: " << graph[i]->edges[k].len << "\n";
        }*/

        if((int)graph[0]->edges.size() < vertnum-1){ // cannot reach all dirt tiles
            cout << "-1\n";
            continue;
        }
        else 
            cout << DFS_bnb(0, 0, 0) << "\n";


    } while(w != 0 || h != 0);


    return 0;
}