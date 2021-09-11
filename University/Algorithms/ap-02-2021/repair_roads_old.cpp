//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstring>
#include <limits>


using namespace std;

struct vert;

struct edge{
    bool* visited;
    vert* to;
};

struct vert{
    short index;
    vector<edge> edges;
} tree[10001];

int count_unvisited(vector<edge> &edges){
    int res = 0;
    for(int n = 0; n < edges.size(); ++n){
        if(!*edges[n].visited) ++res;
    }
    return res;
}

/*
 * Complete the repairRoads function below.
 */
int repairRoads(int n, vector<vector<int>> roads) {
    //cerr << "\t\t==== NEW CASE ====\n";
    int i, j;
    memset(tree, 0, sizeof(tree));
    bool visited[10000] = {0};

    for (i = 0; i < n-1; ++i) {
        edge e;
        e.visited = &visited[i];

        e.to = &tree[roads[i][0]];
        tree[roads[i][1]].index = roads[i][1];
        tree[roads[i][1]].edges.push_back(e);

        e.to = &tree[roads[i][1]];
        tree[roads[i][0]].index = roads[i][0];
        tree[roads[i][0]].edges.push_back(e);
    }
    /*for(i = 0; i < n; ++i){
        //cerr << tree[i].index << ": ";
        for(j = 0; j < tree[i].edges.size(); ++j){
            //cerr << tree[i].edges[j].to->index << "("<< *(tree[i].edges[j].visited) <<") ";
        }
        //cerr << "\n";
    }*/

    int cnt = 0;
    vert* curr_vert;
    bool added, begin;
    int pushed;
    for(i = 0; i < n-1; ++i){ // for each edge
        if(!visited[i]){      // that is not visited
            ++cnt;            // you'll need a robot

            curr_vert = &tree[roads[i][0]]; // take one vertex from edge and start there
            //cerr << "(B)Vertex selected: " << curr_vert->index << "\n";
            queue<vert*> q;  // make a queue to store vertices

           
            for(j = 0; j < (int)curr_vert->edges.size(); ++j){  // for every edge from the vertex
                added = false;
                if(!(*curr_vert->edges[j].visited)){ // if that edge was not visited yet
                    //cerr << "("<< curr_vert->index << ","<< curr_vert->edges[j].to->index <<")?\n";
                    if((int)curr_vert->edges[j].to->edges.size() == 1){ // if edge is pointing to a single vertex
                        //cerr << "(B)Edge visited: ("<< curr_vert->index << ","<< curr_vert->edges[j].to->index <<") - single\n";
                        *(curr_vert->edges[j].visited) = true;          // consider this edge visited
                        added = true;
                    }

                    
                    if((int)curr_vert->edges.size() > 2 && (int)curr_vert->edges[j].to->edges.size() == 2){ // if edge is pointing to a vertex which connects to...
                        vert *new_v = curr_vert->edges[j].to;
                        for(int ix = 0; ix < 2; ++ix){
                            if(new_v->edges[ix].to->index != curr_vert->index){ // edge not pointing back
                                if(new_v->edges[ix].to->edges.size() > 2){      // ... to an edge pointing to multiple other edges
                                    //cerr << "(B)Edge visited: ("<< curr_vert->index << ","<< curr_vert->edges[j].to->index <<") - special branch\n";
                                    *(curr_vert->edges[j].visited) = true;
                                    added = true;
                                    break;
                                }
                            }
                        }
                    }


                    // vertex has many edges = can do further, so add it
                    if(q.size() < 2 && !added){ // two vertices are enough for a start. Expanding path in two directions simultaneously
                        q.push(curr_vert->edges[j].to);
                        //cerr << "(B)Edge visited: ("<< curr_vert->index << ","<< curr_vert->edges[j].to->index <<") ==> pushed\n";
                        *(curr_vert->edges[j].visited) = true; // edge visited
                    }
                    // but continuing the loop to make sure every 'single vertex' will be added above
                }
            }
            begin = true;
            while(!q.empty()){  // here's where the fun begins
                curr_vert = q.front(); // get a new vertex
                q.pop();
                

                // basically copied code from above
                pushed = 1; // make sure only one vertex will be added to continue path
                if(begin && q.size() == 0) pushed = 2;

                //cerr << "Vertex selected: " << curr_vert->index << ", beg:"<<begin<<"\n";
                begin = false;
                
                for(j = 0; j < (int)curr_vert->edges.size(); ++j){  // for every edge from the vertex
                    added = false;
                    if(!(*curr_vert->edges[j].visited)){ // if that edge was not visited yet
                        //cerr << "("<< curr_vert->index << ","<< curr_vert->edges[j].to->index <<")? p: "<<pushed<<"\n";

                        if((int)curr_vert->edges[j].to->edges.size() == 1){ // if edge is pointing to a single vertex
                            *(curr_vert->edges[j].visited) = true;          // consider this edge visited
                            //cerr << "Edge visited: ("<< curr_vert->index << ","<< curr_vert->edges[j].to->index <<") - single\n";
                            added = true;
                        }

                        if((int)curr_vert->edges.size() > 2 && (int)curr_vert->edges[j].to->edges.size() == 2){ // if edge is pointing to a vertex which connects to...
                            vert *new_v = curr_vert->edges[j].to;
                            for(int ix = 0; ix < 2; ++ix){
                                if(new_v->edges[ix].to->index != curr_vert->index){ // edge not pointing back
                                    if(new_v->edges[ix].to->edges.size() > 2){      // ... to an edge pointing to multiple other edges
                                        //cerr << "Edge visited: ("<< curr_vert->index << ","<< curr_vert->edges[j].to->index <<") - special branch\n";
                                        *(curr_vert->edges[j].visited) = true;
                                        added = true;
                                        break;
                                    }
                                }
                            }
                        }

                        // vertex has many edges = can do further, so add it
                        if(pushed > 0 && !added){ // but only if havent added anything already
                            q.push(curr_vert->edges[j].to);
                            --pushed;
                            *(curr_vert->edges[j].visited) = true; // edge visited
                            //cerr << "Edge visited: ("<< curr_vert->index << ","<< curr_vert->edges[j].to->index <<") ==> pushed\n";
                        }
                    }
                }
            }
        }
    }
    //cerr << "\t\t====  DONE  ====\n";
    return cnt;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> roads(n-1);
        for (int roads_row_itr = 0; roads_row_itr < n-1; roads_row_itr++) {
            roads[roads_row_itr].resize(2);

            for (int roads_column_itr = 0; roads_column_itr < 2; roads_column_itr++) {
                cin >> roads[roads_row_itr][roads_column_itr];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int result = repairRoads(n, roads);

        cout << result << "\n";
    }

    //fout.close();

    return 0;
}