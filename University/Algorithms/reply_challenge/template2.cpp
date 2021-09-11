#include <iostream>
#include <cmath>
#include <vector>
#include <valarray>
#include <utility>
#include <cstdlib>
#include <algorithm>

using namespace std;

class KMeans {
public:
    void Kmeans();
    ~KMeans() {}
    KMeans(int k, vector<pair<int, int>>& data_) : m_k(k), m_means(k), m_data(k) {
        m_data[0] = data_;
    }

    void clusterData(valarray<pair<int, int>>& init_means_, int num_iters_) {
        m_means = init_means_;
        this->assignLabels();

        int i = 0;
        while (i < num_iters_) {
            cout<<"running iteration:" << i <<"\n";
            this->computeMeans();
            this->assignLabels();
            i++;
        }
        return;
    }

    void printClusters() const {
        for (int i = 0; i < m_k; i++) {
            for (const auto& it : m_data[i]) {
                cout << "[" << get<0>(it) << ", " << get<1>(it) << "]";
            }
            cout << "\r\n";
        }
    }

private:

    bool computeMeans() {
        bool res = true;
        for (int i = 0; i < m_k; i++) {
            pair<int, int> mean(0, 0);
            int num_of_k = m_data[i].size();
            for (auto const& it : m_data[i]) {
                get<0>(mean) += get<0>(it);
                get<1>(mean) += get<1>(it);
            }

            get<0>(mean) /= num_of_k;
            get<1>(mean) /= num_of_k;
            res = (m_means[i] == mean && res == true) ? true : false;
            m_means[i] = mean;
            cout << "cluster centroid x: " <<get<0>(mean) << " , y " << get<1>(mean) <<"\t";
        }
        cout << "\r\n";
        return res;
    }

    void assignLabels() {
        valarray<vector<pair<int, int>>> new_data(m_k);
        for (auto const& clust : m_data) {
            for (auto const& feature : clust) {
                int closest_mean = this->computeClosestCentroid(feature);
                new_data[closest_mean].push_back(feature);
            }
        }
        m_data = new_data;
        return;
    }

    int computeClosestCentroid(const pair<int, int>& point_) {
        valarray<int> distances(m_k);
        for (int i = 0; i < m_k; ++i) {
            int del_x = get<0>(point_) - get<0>(m_means[i]);
            int del_y = get<1>(point_) - get<1>(m_means[i]);
            int dist = abs(del_x) + abs(del_y);
            distances[i] = dist;
        }
        auto closest_mean = distance(begin(distances), min_element(begin(distances), end(distances)));
        return closest_mean;
    }

    int m_k;
    int m_features;
    //current means
    valarray<pair<int, int>> m_means;
    //array of vectors holding coordinates
    valarray<vector<pair<int, int>>> m_data;
};


int main() {
    ios_base::sync_with_stdio(0);
    vector<pair<int, int>> data = {{0,7},{12,2},{2,4},{10,7},{11,8}};

    KMeans km(4, data);

    valarray<pair<int, int>> init_means_ = { { 0,8 }, {12,2}, {10,7} };

    km.clusterData(init_means_, init_means_.size());

    km.printClusters();

    return 0;
}