#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

// Maximum Bipartite Matching for Unweighted Graph
class Hungarian {
public:
    explicit Hungarian(int n_u, int n_v) :
    num_vertices_U_(n_u), num_vertices_V_(n_v), g_(n_u + n_v) {
        g_.AddEdge(0, 4);
        g_.AddEdge(0, 5);
        g_.AddEdge(1, 5);
        g_.AddEdge(1, 6);
        g_.AddEdge(2, 4);
        g_.AddEdge(2, 5);
        g_.AddEdge(3, 6);

        total_num_ = n_u + n_v;
        for (int i = 0; i < total_num; i++) {
            matching_[i] = -1;
        }
    }

    void Run() {
        int total_matching = 0;
        for (int i = 0; i < num_vertices_U_; i++) {
            visited_.assign(num_vertices_V_, false);
            if (FindMatching(i)) {
                total_matching++;
            }
        }

        std::cout << "Total = " << total_matching << std::endl;
        for (int i = 0; i < num_vertices_U_; i++) {
            std::cout << i << " -> " << matching_[i] << std::endl;
        }
    }

private:
    Graph g_;
    int num_vertices_U_, num_vertices_V_;
    int total_num_;
    std::vector<bool> visited_;
    std::map<int, int> matching_;

    bool FindMatching(int u) {
        // iterating sets V      
        for (unsigned int v = num_vertices_U_; v < total_num_; v++) {
            // if there is a edge between vertices from U and V
            bool is_connected = 
                std::find(g_.adj_list_[u].cbegin(), g_.adj_list_[u].cend(), v) 
                != g_.adj_list_[u].cend();
            // augmenting path - unmatched -> matched -> ... -> matched -> unmatched
            if (false == visited_[v] && is_connected) {
                visited_[v] = true;
                // if vertex in V is not matched, we will match it
                // if it is matched already, we then go back to set U
                // we will try to figure out if the vertex from U can be 
                // matched with another vertex in V
                // remember unmatched -> matched -> unmatched -> .....
                if (-1 == matching_[v] || FindMatching(matching_[v])) {
                    matching_[v] = u;
                    matching_[u] = v;
                    return true;
                }
            }
        }
        return false;
    } // end of FindMatching function
}; // end of class


int main() {
    // number of vertices on two independent sets U and V
    Hungarian hungarian(4, 4);
    hungarian.Run();
    return 0;
}